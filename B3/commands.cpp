#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <sstream>

using namespace std::placeholders;

const auto reportInvalid = std::bind([](std::ostream& output){ output << "<INVALID COMMAND>\n"; }, _2);

commands::execute_command commands::parseTaskArguments(std::istream& input)
{
  struct command_t
  {
    const char* name;
    std::function<execute_command(std::istream&)> action;
  };

  static const command_t commands[] =
    {
      {"add", &parseAddArguments},
      {"store", &parseStoreArguments},
      {"insert", &parseInsertArguments},
      {"delete", &parseDeleteArguments},
      {"show", &parseShowArguments},
      {"move", &parseMoveArguments}
    };

  input >> std::noskipws;

  std::string commandName;
  input >> commandName;

  auto command = std::find_if(std::begin(commands), std::end(commands),
                              [&](const command_t& command) {return commandName == command.name;});

  if (command != std::end(commands))
  {
    return command->action(input);
  }
  else
  {
    return reportInvalid;
  }
}

commands::execute_command commands::parseAddArguments(std::istream& input)
{
  std::string number = commands::readNumberFromStream(input);
  std::string name = commands::readNameFromStream(input);
  if (number.empty() || name.empty())
  {
    return reportInvalid;
  }

  Phonebook::record_t record = {name, number};

  return std::bind(
    [&](BookmarkManager& manager, const Phonebook::record_t& record){ manager.add(record); }, _1, record);
}

commands::execute_command commands::parseStoreArguments(std::istream& input)
{
  std::string bookmark = commands::readBookmarkFromStream(input);
  std::string newBookmark = commands::readBookmarkFromStream(input);
  if (bookmark.empty() || newBookmark.empty())
  {
    return reportInvalid;
  }

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return reportInvalid;
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark, const std::string& newBookmark)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      manager.store(bookmark, newBookmark);
    }, _1, _2, bookmark, newBookmark);
}

commands::execute_command commands::parseInsertArguments(std::istream& input)
{
  struct insert_positions_t
  {
    const char* name;
    insert_position position;
  };

  static const insert_positions_t InsertPositions[] =
    {
      {"before", insert_position::before},
      {"after", insert_position::after}
    };

  std::string position;
  input >> commands::blank >> position;

  auto insertPosition = std::find_if(std::begin(InsertPositions), std::end(InsertPositions),
                                     [&](const insert_positions_t& insertPosition) { return position == insertPosition.name; });

  if (insertPosition == std::end(InsertPositions))
  {
    return reportInvalid;
  }

  std::string bookmark = commands::readBookmarkFromStream(input);
  std::string number = commands::readNumberFromStream(input);
  std::string name = commands::readNameFromStream(input);

  if (bookmark.empty() || number.empty() || name.empty())
  {
    return reportInvalid;
  }

  Phonebook::record_t record = {name, number};

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output,
        const std::string& bookmark, const Phonebook::record_t& record, insert_position position)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      manager.insert(bookmark, record, position);
    }, _1, _2, bookmark, record, insertPosition->position);
}

commands::execute_command commands::parseDeleteArguments(std::istream& input)
{
  std::string bookmark = commands::readBookmarkFromStream(input);
  if (bookmark.empty())
  {
    return reportInvalid;
  }

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return reportInvalid;
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      if (!manager.bookmarkValid(bookmark))
      {
        output << "<INVALID COMMAND>\n";

        return;
      }

      manager.remove(bookmark);
    }, _1, _2, bookmark);
}

commands::execute_command commands::parseShowArguments(std::istream& input)
{
  std::string bookmark = commands::readBookmarkFromStream(input);
  if (bookmark.empty())
  {
    return reportInvalid;
  }

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return reportInvalid;
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      if (manager.recordsEmpty())
      {
        output << "<EMPTY>\n";

        return;
      }

      if (!manager.bookmarkValid(bookmark))
      {
        return;
      }

      manager.show(bookmark, output);
    }, _1, _2, bookmark);
}

commands::execute_command commands::parseMoveArguments(std::istream& input)
{
  struct move_positions_t
  {
    const char* name;
    move_position position;
  };

  static const move_positions_t MovePositions[] =
    {
      {"first", move_position::first},
      {"last", move_position::last}
    };

  std::string bookmark = commands::readBookmarkFromStream(input);
  if (bookmark.empty())
  {
    return reportInvalid;
  }

  std::string steps;
  input >> blank >> steps;

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return reportInvalid;
  }

  auto movePosition = std::find_if(std::begin(MovePositions), std::end(MovePositions),
                                   [&](const move_positions_t& movePosition) { return steps == movePosition.name; });

  if (movePosition == std::end(MovePositions))
  {
    int multiplier = 1;
    if (*steps.begin() == '-')
    {
      multiplier = -1;
      steps.erase(steps.begin());
    }
    else if (*steps.begin() == '+')
    {
      steps.erase(steps.begin());
    }

    auto it = std::find_if(steps.begin(), steps.end(),
                           [&](auto digit){ return !std::isdigit(digit); });

    if (it != steps.end())
    {
      return std::bind([&](std::ostream& output){ output << "<INVALID STEP>\n"; }, _2);
    }

    return std::bind(
      [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark, int steps)
      {
        if (!manager.bookmarkExists(bookmark))
        {
          output << "<INVALID BOOKMARK>\n";

          return;
        }

        manager.move(bookmark, steps);
      }, _1, _2, bookmark, std::stoi(steps) * multiplier);
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark, move_position position)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      manager.move(bookmark, position);
    }, _1, _2, bookmark, movePosition->position);
}

std::string commands::readBookmarkFromStream(std::istream& input)
{
  std::string bookmark;
  input >> blank >> bookmark;

  auto it = std::find_if(bookmark.begin(), bookmark.end(),
                         [&](auto character){ return (!std::isalnum(character) && !(character == '-')); });

  if (it != bookmark.end())
  {
    return "";
  }

  return bookmark;
}

std::string commands::readNumberFromStream(std::istream& input)
{
  std::string number;
  input >> blank >> number;

  auto it = std::find_if(number.begin(), number.end(),
                         [&](auto digit){ return !std::isdigit(digit); });

  if (it != number.end())
  {
    return "";
  }

  return number;
}

std::string commands::readNameFromStream(std::istream& input)
{
  if ((input >> blank).peek() != '\"')
  {
    return "";
  }

  std::string name;
  std::getline(input, name);
  if (name.back() != '\"')
  {
    return "";
  }

  std::stringstream namestream(name);
  std::string quoted;
  namestream >> std::quoted(quoted);

  if (quoted.empty())
  {
    return "";
  }

  std::string extraData;
  std::getline(input >> blank, extraData);
  if (!extraData.empty())
  {
    return "";
  }

  return quoted;
}
  
template <typename Char, typename Traits>
std::basic_istream<Char, Traits>& commands::blank(std::basic_istream<Char, Traits>& input)
{
  using istream_type = std::basic_istream<Char, Traits>;
  using streambuf_type = std::basic_streambuf<Char, Traits>;
  using int_type = typename istream_type::int_type;
  using ctype_type = std::ctype<Char>;
  
  const ctype_type& ct = std::use_facet<ctype_type>(input.getloc());
  const int_type eof = Traits::eof();
  streambuf_type* sb = input.rdbuf();
  int_type c = sb->sgetc();

  while (!Traits::eq_int_type(c, eof) && ct.is(std::ctype_base::blank, Traits::to_char_type(c)))
  {
    c = sb->snextc();
  }
  if (Traits::eq_int_type(c, eof))
  {
    input.setstate(std::ios_base::eofbit);
  }

  return input;
  }

