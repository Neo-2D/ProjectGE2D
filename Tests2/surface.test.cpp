#include "pch.h"
#include "string"
#include "../GE2D/Surface.cpp"
#include "../GE2D/Vector2D.hpp"

const float EPSILON = 1e-5; // Tolerance for floating-point comparison

TEST(SurfaceTest, ConstructorAndGetters) {
	const std::string surfacePath = "assets/surface.png";
	Surface s(surfacePath, 8, 8);
	EXPECT_NEAR(s.getBaseWidth(), 8, EPSILON);
	EXPECT_NEAR(s.getBaseHeight(), 8, EPSILON);
	EXPECT_EQ(s.getPath(), surfacePath);
}