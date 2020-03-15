#define BOOST_TEST_MODULE A2

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "polygon.hpp"

#define EPSILON 1e-10

BOOST_AUTO_TEST_SUITE(shapeRectangle)
  
  BOOST_AUTO_TEST_CASE(RectangleAfterShiftMove)
  {

    dusaeva::Rectangle testRectangle({5.0, 2.0}, 6.9, 7.0);
    const dusaeva::rectangle_t rectBeforeMove = testRectangle.getFrameRect();
    const double areaBeforeMoving = testRectangle.getArea();

    testRectangle.move(4.5, 6.0);

    const dusaeva::rectangle_t rectAfterMoving = testRectangle.getFrameRect();
    const double areaAfterMoving = testRectangle.getArea();

    BOOST_CHECK_CLOSE(rectAfterMoving.width, rectBeforeMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectAfterMoving.height, rectBeforeMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaAfterMoving, areaBeforeMoving, EPSILON);

  }

  BOOST_AUTO_TEST_CASE(RectangleAfterPointMove)
  {

    dusaeva::Rectangle testRectangle({5.0, 2.0}, 6.9, 7.0);
    const dusaeva::rectangle_t rectBeforeMove = testRectangle.getFrameRect();
    const double areaBeforeMoving = testRectangle.getArea();

    testRectangle.move({1.3, 5.6});

    const dusaeva::rectangle_t rectAfterMoving = testRectangle.getFrameRect();
    const double areaAfterMove = testRectangle.getArea();

    BOOST_CHECK_CLOSE(rectAfterMoving.width, rectBeforeMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectAfterMoving.height, rectBeforeMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMoving, EPSILON);

  }

  BOOST_AUTO_TEST_CASE(RectangleAfterScale)
  {
    const double scale = 1.5;
    const double declineScale = 0.5;
    dusaeva::Rectangle testRectangle{{0.6, 4.5}, 5.0, 6.0};
    double areaBeforeScale = testRectangle.getArea();
    testRectangle.scale(scale);
    double areaAfterScale = testRectangle.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);

    areaBeforeScale = testRectangle.getArea();
    testRectangle.scale(declineScale);
    areaAfterScale = testRectangle.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * declineScale * declineScale), areaAfterScale, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(RectangleAfterRotate)
  {
    dusaeva::Rectangle testRectangle({5.0, 2.0}, 6.9, 7.0);
    const double areaBeforeMoving = testRectangle.getArea();
    testRectangle.rotate(65);
  
    const double areaAfterMove = testRectangle.getArea();
    BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMoving, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(RectangleIncorrectParameters)
  {
    dusaeva::Rectangle testRectangle({1.0, 6.0}, 5.0, 4.0);

    BOOST_CHECK_THROW(dusaeva::Rectangle incorrectRectangle1({1.0, 6.0}, 5.0, -4.0), std::invalid_argument);
    BOOST_CHECK_THROW(dusaeva::Rectangle incorrectRectangle2({1.0, 6.0}, -5.0, 4.0), std::invalid_argument);
    BOOST_CHECK_THROW(testRectangle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(shapeCircle)

  BOOST_AUTO_TEST_CASE(CircleAfterShiftMove)
  {
    const double radius = 6.5;
    dusaeva::Circle testCircle({1.0, 2.0}, radius);

    const dusaeva::rectangle_t rectBeforeMove = testCircle.getFrameRect();
    const double areaBeforeMove = testCircle.getArea();

    testCircle.move(3.0, 6.1);

    const dusaeva::rectangle_t rectAfterMove = testCircle.getFrameRect();
    const double areaAfterMove = testCircle.getArea();

    BOOST_CHECK_CLOSE(rectAfterMove.width, rectBeforeMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectAfterMove.height, rectBeforeMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMove, EPSILON);
  }

BOOST_AUTO_TEST_CASE(CircleAfterPointMove)
  {
    const double radius = 6.5;
    dusaeva::Circle testCircle({1.0, 2.0}, radius);

    const dusaeva::rectangle_t rectBeforeMove = testCircle.getFrameRect();
    const double areaBeforeMove = testCircle.getArea();

    testCircle.move({1.0, 5.0});

    const dusaeva::rectangle_t rectAfterMove = testCircle.getFrameRect();
    const double areaAfterMove = testCircle.getArea();

    BOOST_CHECK_CLOSE(rectAfterMove.width, rectBeforeMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectAfterMove.height, rectBeforeMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaAfterMove, areaBeforeMove, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(CircleAfterScale)
  {
    const double scale = 2.5;
    const double declineScale = 0.5;
    dusaeva::Circle testCircle({8.0, 6.5}, 9.0);

    double areaBeforeScale = testCircle.getArea();
    testCircle.scale(scale);
    double areaAfterScale = testCircle.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);

    areaBeforeScale = testCircle.getArea();
    testCircle.scale(declineScale);
    areaAfterScale = testCircle.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * declineScale * declineScale), areaAfterScale, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(CircleAfterRotate)
  {
    const double radius = 6.5;
    dusaeva::Circle testCircle({1.0, 2.0}, radius);
    const double areaBeforeRotate = testCircle.getArea();
    
    testCircle.rotate(90);
    
    const double areaAfterRotate = testCircle.getArea();
    BOOST_CHECK_CLOSE(areaBeforeRotate, areaAfterRotate, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(CircleIncorrectParameters)
  {
    dusaeva::Circle testCircle({2.0, -6.0}, 4.3);

    BOOST_CHECK_THROW(testCircle.scale(-3.0), std::invalid_argument);
    BOOST_CHECK_THROW(dusaeva::Circle wrongCircle({2.0, -6.0}, -4.3), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(shapeTriangle)

  BOOST_AUTO_TEST_CASE(TriangleAfterShiftMove)
  {
    dusaeva::Triangle testTriangle({6.9, 7.0}, {1.2, 0.3}, {3.1, 1.6});
    const dusaeva::rectangle_t rectBeforeMove = testTriangle.getFrameRect();
    const double areaBeforeMove = testTriangle.getArea();

    testTriangle.move(4.5, 6.0);

    const dusaeva::rectangle_t rectAfterMove = testTriangle.getFrameRect();
    const double areaAfterMove = testTriangle.getArea();

    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);
  }
  
    BOOST_AUTO_TEST_CASE(TriangleAfterPointMove)
  {

    dusaeva::Triangle testTriangle({6.9, 7.0}, {1.2, 0.3}, {3.1, 1.6});
    const dusaeva::rectangle_t rectBeforeMove = testTriangle.getFrameRect();
    const double areaBeforeMove = testTriangle.getArea();

    testTriangle.move({1.3, 5.6});

    const dusaeva::rectangle_t rectAfterMove = testTriangle.getFrameRect();
    const double areaAfterMove = testTriangle.getArea();

    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);  
  }
  
  BOOST_AUTO_TEST_CASE(TriangleAfterRotate)
  {
    dusaeva::Triangle testTriangle({6.9, 7.0}, {1.2, 0.3}, {3.1, 1.6});
    const double areaBeforeRotate = testTriangle.getArea();
    const dusaeva::point_t centerBeforeRotate = testTriangle.getCenter();
    
    testTriangle.rotate(56);
    
    const double areaAfterRotate = testTriangle.getArea();
    
    BOOST_CHECK_CLOSE(centerBeforeRotate.x, testTriangle.getCenter().x, EPSILON);
    BOOST_CHECK_CLOSE(centerBeforeRotate.y, testTriangle.getCenter().y, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeRotate, areaAfterRotate, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(TriangleAfterScale)
  {
    const double scale = 3.0;
    const double declineScale = 0.3;
    dusaeva::Triangle testTriangle({4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0});

    double areaBeforeScale = testTriangle.getArea();
    testTriangle.scale(scale);
    double areaAfterScale = testTriangle.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);

    areaBeforeScale = testTriangle.getArea();
    testTriangle.scale(declineScale);
    areaAfterScale = testTriangle.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * declineScale * declineScale), areaAfterScale, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(TriangleWrongParameters)
  {
    dusaeva::Triangle testTriangle({6.9, 7.0}, {1.2, 0.3}, {3.1, 1.6});
    BOOST_CHECK_THROW(testTriangle.scale(-2.0), std::invalid_argument);

    BOOST_CHECK_THROW(dusaeva::Triangle incorrectTriangle_1({1.0, 7.0}, {1.0, 6.5}, {1.0, 8.0}), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(shapePolygon)

  BOOST_AUTO_TEST_CASE(copyConstructor)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;
    dusaeva::Polygon copiedPolygon(testPolygon);

    BOOST_CHECK_CLOSE(copiedPolygon.getArea(), testPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().height, testPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().width, testPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().pos.x, testPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(copiedPolygon.getFrameRect().pos.y, testPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(moveConstructor)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;
    double areaBefore = testPolygon.getArea();
    dusaeva::rectangle_t frameRectBefore = testPolygon.getFrameRect();
    dusaeva::Polygon movedPolygon(std::move(testPolygon));

    BOOST_CHECK_CLOSE(areaBefore, movedPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.height, movedPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.width, movedPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.x, movedPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.y, movedPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(copyAssignmentOperator)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;
    dusaeva::point_t *points1 = new dusaeva::point_t[3]{{4.0, 12.0}, {15.0, 6.0}, {1.0, 1.0}};
    dusaeva::Polygon copiedPolygon(3, points1);
    delete[] points1;
    copiedPolygon = testPolygon;

    BOOST_CHECK_CLOSE(testPolygon.getArea(), copiedPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().height, copiedPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().width, copiedPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().pos.x, copiedPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(testPolygon.getFrameRect().pos.y, copiedPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(moveAssignmentOperator)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;

    double areaBefore = testPolygon.getArea();
    dusaeva::rectangle_t frameRectBefore = testPolygon.getFrameRect();
    dusaeva::point_t *points1 = new dusaeva::point_t[3]{{4.0, 12.0}, {15.0, 6.0}, {1.0, 1.0}};
    dusaeva::Polygon movedPolygon(3, points1);
    delete[] points1;
    movedPolygon = std::move(testPolygon);
    BOOST_CHECK_CLOSE(areaBefore, movedPolygon.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.height, movedPolygon.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.width, movedPolygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.x, movedPolygon.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBefore.pos.y, movedPolygon.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(PolygonAfterShiftMove)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;    
    const dusaeva::rectangle_t rectBeforeMove = testPolygon.getFrameRect();
    const double areaBeforeMove = testPolygon.getArea();

    testPolygon.move(0.5, 6.0);

    const dusaeva::rectangle_t rectAfterMove = testPolygon.getFrameRect();
    const double areaAfterMove = testPolygon.getArea();

    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);
  }

    BOOST_AUTO_TEST_CASE(PolygonAfterPointMove)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;
    const dusaeva::rectangle_t rectBeforeMove = testPolygon.getFrameRect();
    const double areaBeforeMove = testPolygon.getArea();

    testPolygon.move({0.4, 5.0});

    const dusaeva::rectangle_t rectAfterMove = testPolygon.getFrameRect();
    const double areaAfterMove = testPolygon.getArea();

    BOOST_CHECK_CLOSE(rectBeforeMove.width, rectAfterMove.width, EPSILON);
    BOOST_CHECK_CLOSE(rectBeforeMove.height, rectAfterMove.height, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeMove, areaAfterMove, EPSILON);  
  }
  
  BOOST_AUTO_TEST_CASE(PolygonAfterScale)
  {
    const double scale = 5.0;
    const double declineScale = 0.6;
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;

    double areaBeforeScale = testPolygon.getArea();
    testPolygon.scale(scale);
    double areaAfterScale = testPolygon.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * scale * scale), areaAfterScale, EPSILON);

    areaBeforeScale = testPolygon.getArea();
    testPolygon.scale(declineScale);
    areaAfterScale = testPolygon.getArea();
    BOOST_CHECK_CLOSE((areaBeforeScale * declineScale * declineScale), areaAfterScale, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(PolygonAfterRotate)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;
    const double areaBeforeRotate = testPolygon.getArea();
    const dusaeva::point_t centerBeforeRotate = testPolygon.getCenter();
  
    testPolygon.rotate(67);
    
    const double areaAfterRotate = testPolygon.getArea();
    
    BOOST_CHECK_CLOSE(centerBeforeRotate.x, testPolygon.getCenter().x, EPSILON);
    BOOST_CHECK_CLOSE(centerBeforeRotate.y, testPolygon.getCenter().y, EPSILON);
    BOOST_CHECK_CLOSE(areaBeforeRotate, areaAfterRotate, EPSILON);
  }
  
  BOOST_AUTO_TEST_CASE(PolygonWrongParameters)
  {
    dusaeva::point_t *points = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {-2.0, 6.0}};
    dusaeva::Polygon testPolygon(4, points);
    delete[] points;    
    BOOST_CHECK_THROW(testPolygon.scale(-2.0), std::invalid_argument);
    //количество сторон
    dusaeva::point_t *points1 = new dusaeva::point_t[2]{{4.0, 10.0}, {15.0, 6.0}};
    BOOST_CHECK_THROW(dusaeva::Polygon incorrectPolygon1(2, points1), std::invalid_argument);
    delete[] points1;

    //проверка на вырожденность
    dusaeva::point_t *points2 = new dusaeva::point_t[4]{{4.0, 10.0}, {4.0, 6.0}, {4.0, 1.0}, {4.0, 6.0}};
    BOOST_CHECK_THROW(dusaeva::Polygon incorrectPolygon2(4, points2), std::invalid_argument);
    delete[] points2;

    //выпуклость
    dusaeva::point_t *points3 = new dusaeva::point_t[4]{{4.0, 10.0}, {15.0, 6.0}, {1.0, 1.0}, {5.0, 5.0}};
    BOOST_CHECK_THROW(dusaeva::Polygon incorrectPolygon3(4, points3), std::invalid_argument);
    delete[] points3;
  }

BOOST_AUTO_TEST_SUITE_END()

