#include "pch.h"
#include "../GE2D/Vector2D.cpp"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


const float EPSILON = 1e-5; // Tolerance for floating-point comparison
namespace MathTests {

    TEST(Vector2DTest, ConstructorAndGetters) {
        Vector2D v(3.0f, 4.0f);
        EXPECT_NEAR(v.getX(), 3.0f, EPSILON);
        EXPECT_NEAR(v.getY(), 4.0f, EPSILON);
    }

    TEST(Vector2DTest, Setters) {
        Vector2D v(0.0f, 0.0f);
        v.setX(5.0f);
        v.setY(6.0f);
        EXPECT_NEAR(v.getX(), 5.0f, EPSILON);
        EXPECT_NEAR(v.getY(), 6.0f, EPSILON);
    }

    TEST(Vector2DTest, AdditionOperator) {
        Vector2D v1(1.0f, 2.0f);
        Vector2D v2(3.0f, 4.0f);
        Vector2D result = v1 + v2;
        EXPECT_NEAR(result.getX(), 4.0f, EPSILON);
        EXPECT_NEAR(result.getY(), 6.0f, EPSILON);
    }

    TEST(Vector2DTest, SubtractionOperator) {
        Vector2D v1(5.0f, 7.0f);
        Vector2D v2(3.0f, 4.0f);
        Vector2D result = v1 - v2;
        EXPECT_NEAR(result.getX(), 2.0f, EPSILON);
        EXPECT_NEAR(result.getY(), 3.0f, EPSILON);
    }

    TEST(Vector2DTest, ScalarMultiplicationOperator) {
        Vector2D v(2.0f, 3.0f);
        Vector2D result = v * 2.0f;
        EXPECT_NEAR(result.getX(), 4.0f, EPSILON);
        EXPECT_NEAR(result.getY(), 6.0f, EPSILON);
    }

    TEST(Vector2DTest, ScalarDivisionOperator) {
        Vector2D v(4.0f, 8.0f);
        Vector2D result = v / 2.0f;
        EXPECT_NEAR(result.getX(), 2.0f, EPSILON);
        EXPECT_NEAR(result.getY(), 4.0f, EPSILON);
    }

    TEST(Vector2DTest, Equals) {
        Vector2D v1(3.0f, 4.0f);
        Vector2D v2(3.0f, 4.0f);
        EXPECT_TRUE(v1.equals(v2));
    }

    TEST(Vector2DTest, DotProduct) {
        Vector2D v1(1.0f, 2.0f);
        Vector2D v2(3.0f, 4.0f);
        float result = v1.dot(v2);
        EXPECT_NEAR(result, 11.0f, EPSILON);
    }

    TEST(Vector2DTest, CrossProduct) {
        Vector2D v1(1.0f, 2.0f);
        Vector2D v2(3.0f, 4.0f);
        float result = v1.cross(v2);
        EXPECT_NEAR(result, -2.0f, EPSILON);
    }

    TEST(Vector2DTest, Magnitude) {
        Vector2D v(3.0f, 4.0f);
        EXPECT_NEAR(v.magnitude(), 5.0f, EPSILON);
    }

    TEST(Vector2DTest, Orientation) {
        Vector2D v(0.0f, 1.0f);
        EXPECT_NEAR(v.orientation(), M_PI / 2, EPSILON);
    }

    TEST(Vector2DTest, Normalize) {
        Vector2D v(3.0f, 4.0f);
        Vector2D result = v.normalize();
        EXPECT_NEAR(result.magnitude(), 1.0f, EPSILON);
    }

    TEST(Vector2DTest, ProjectOnto) {
        Vector2D v1(2.0f, 3.0f);
        Vector2D v2(5.0f, 0.0f);
        Vector2D result = v1.projectOnto(v2);
        EXPECT_NEAR(result.getX(), 2.0f, EPSILON);
        EXPECT_NEAR(result.getY(), 0.0f, EPSILON);
    }

    TEST(Vector2DTest, Rotate) {
        Vector2D v(1.0f, 0.0f);
        Vector2D result = v.rotate(M_PI / 2);  // Rotate 90 degrees
        EXPECT_NEAR(result.getX(), 0.0f, EPSILON);
        EXPECT_NEAR(result.getY(), 1.0f, EPSILON);
    }
}
