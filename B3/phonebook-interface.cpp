#include "phonebook-interface.hpp"
#include <algorithm>
#include <iostream>

BookmarkManager::BookmarkManager()
{
  bookmarks_["current"] = records_.end();
}

void BookmarkManager::add(const Phonebook::record_t& record)
{
  records_.push_back(record);

  if (std::next(records_.begin()) == records_.end())
  {
    bookmarks_["current"] = records_.begin();
  }
}

void BookmarkManager::store(const std::string& bookmark, const std::string& newBookmark)
{
  auto iter = getElementIterator(bookmark);

  bookmarks_.emplace(newBookmark, iter->second);
}

void BookmarkManager::insert(const std::string& bookmark, const Phonebook::record_t& record, InsertPosition position)
{
  auto iter = getElementIterator(bookmark);

  if (iter->second == records_.end())
  {
    add(record);

    return;
  }

  auto pos = (position == InsertPosition::before) ? iter->second : std::next(iter->second);

  records_.insert(pos, record);
}

void BookmarkManager::remove(const std::string& bookmark)
{
  auto iter = getElementIterator(bookmark);

  if (iter->second == records_.end())
  {
    throw std::invalid_argument("The element to remove does not exist.");
  }

  auto current = iter->second;

  std::for_each(bookmarks_.begin(), bookmarks_.end(),
                [&](auto& bookmark){ if (bookmark.second == current) bookmark.second = std::next(current); });

  records_.erase(current);

  std::for_each(bookmarks_.begin(), bookmarks_.end(),
                [&](auto& bookmark){ if (bookmark.second == records_.end()) bookmark.second = std::prev(records_.end()); });
}

void BookmarkManager::show(const std::string& bookmark, std::ostream& output)
{
  auto iter = getElementIterator(bookmark);

  if (iter->second == records_.end())
  {
    throw std::invalid_argument("The records list is empty.");
  }

  output << iter->second->number << " " << iter->second->name << "\n";
}

void BookmarkManager::move(const std::string& bookmark, int steps)
{
  auto iter = getElementIterator(bookmark);

  std::advance(iter->second, steps);
}

void BookmarkManager::move(const std::string& bookmark, MovePosition position)
{
  auto iter = getElementIterator(bookmark);

  auto newPos = (position == MovePosition::first) ? records_.begin() : std::prev(records_.end());

  iter->second = newPos;
}

void BookmarkManager::moveNext(const std::string& bookmark)
{
  move(bookmark, 1);
}

void BookmarkManager::movePrev(const std::string& bookmark)
{
  move(bookmark, -1);
}

void BookmarkManager::replace(const std::string& bookmark, const Phonebook::record_t& record)
{
  auto iter = getElementIterator(bookmark);

  *(iter->second) = record;
}

bool BookmarkManager::bookmarkExists(const std::string& bookmark) const
{
  auto iter = bookmarks_.find(bookmark);

  return iter != bookmarks_.end();
}

bool BookmarkManager::bookmarkValid(const std::string& bookmark)
{
  auto iter = getElementIterator(bookmark);

  return iter->second != records_.end();
}

bool BookmarkManager::recordsEmpty() const
{
  return records_.empty();
}

BookmarkManager::bookmarks::iterator BookmarkManager::getElementIterator(const std::string& bookmark)
{
  auto iter = bookmarks_.find(bookmark);

  if (iter != bookmarks_.end())
  {
    return iter;
  }

  throw std::invalid_argument("The bookmark does not exist.");
}
