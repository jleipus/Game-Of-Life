#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "../rectangle.h"
#include "../cell.h"
#include "../ruleset.h"
#include "../gamefield.h"

#define ALIVE 1
#define DEAD 0

TEST_CASE("Rectangle cen store coordinates and measurements", "[rectangle]") {
	
	int left = 1;
    int right = 3;
    int top = 1;
    int bottom = 3;
    int width = 2;
    int height = 2;
	
	Rectangle r(left, right, top, bottom, width, height);		
	
	REQUIRE(r.left == left);
	REQUIRE(r.right == right);
	REQUIRE(r.top == top);
	REQUIRE(r.bottom == bottom);
	REQUIRE(r.width == width);
	REQUIRE(r.height == height);
}

TEST_CASE("Cell can store and return value and neighbours", "[cell]") {
	
	//     x  y  value
	Cell c(0, 0, ALIVE);
	
	SECTION("getValue returns value") {
		REQUIRE(c.getValue() == ALIVE);
	}
	
	SECTION("setValue sets value") {
		c.setValue(DEAD);
		REQUIRE(c.getValue() == DEAD);
	}
	
	SECTION("getNeighbours returns default value of 0") {
		REQUIRE(c.getNeighbours() == 0);
	}
	
	SECTION("setNeighbours sets neighbour count") {
		int neighbours = 3;
		
		c.setNeighbours(neighbours);
		
		REQUIRE(c.getValue() == neighbours);
	}
	
	SECTION("getRectangle returns rectangle with all measurements") {
		int left = 0;
		int right = Cell::CELL_SIZE;
		int top = 0;
		int bottom = Cell::CELL_SIZE;
		int width = Cell::CELL_SIZE;
		int height = Cell::CELL_SIZE;	

		Rectangle r = c.getRectangle();
	
		REQUIRE(r.left == left);
		REQUIRE(r.right == right);
		REQUIRE(r.top == top);
		REQUIRE(r.bottom == bottom);
		REQUIRE(r.width == width);
		REQUIRE(r.height == height);
	}
}

TEST_CASE("Ruleset has methods for determining outcomes and counting neighbours", "[ruleset]") {
	
	SECTION("getOutcome calculates next cycle outcomes for cells") {
		
		int cellValue;
		int neighbourCount;
		
		SECTION("any live cell with fewer than two live neighbours dies") {
			cellValue = ALIVE;
			
			neighbourCount = 1;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
			
			neighbourCount = 0;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
		}
		
		SECTION("any live cell with two or three live neighbours lives on") {
			cellValue = ALIVE;
			
			neighbourCount = 2;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == ALIVE);
			
			neighbourCount = 3;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == ALIVE);
		}
		
		SECTION("any live cell with more than three live neighbours dies") {
			cellValue = ALIVE;
			
			neighbourCount = 4;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
			
			neighbourCount = 5;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
			
			neighbourCount = 6;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
			
			neighbourCount = 7;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
			
			neighbourCount = 8;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == DEAD);
		}
		
		SECTION("any dead cell with exactly three live neighbours becomes a live cell") {
			cellValue = DEAD;
			neighbourCount = 3;
			REQUIRE(Ruleset::getOutcome(cellValue, neighbourCount) == ALIVE);
		}
	}
	
	SECTION("getNeighbourCount count how many live neighbours a cell has") {
		GameField g();
		
		//     0 1 2
		//
		// 0   x 1 0
		// 1   1 1 0
		// 2   0 0 1
		
		g.setCell(0, 1, ALIVE);
		g.setCell(1, 0, ALIVE);
		g.setCell(1, 1, ALIVE);
		g.setCell(2, 2, ALIVE);
		
		REQUIRE(Ruleset::getNeighbourCount(0, 0, &g) == 3);
	}
}

TEST_CASE("GameField can be resized and store cells", "[gamefield]") {
	
	GameField g();
	
	SECTION("getCellValue returns specific cells value") {
		int x = 1;
		int y = 1;
		
		REQUIRE(g.getCellValue(x, y) == DEAD);
	}
	
	SECTION("setCellValue sets specific cells value") {
		int x = 1;
		int y = 1;
		
		g.setCellValue(x, y, ALIVE);
		
		REQUIRE(g.getCellValue(x, y) == ALIVE);
	}
	
	SECTION("getCellNeighbours returns specific cells default neighbour count of 0") {
		int x = 1;
		int y = 1;
		
		REQUIRE(g.getCellNeighbours(x, y) == 0);
	}
	
	SECTION("setCellNeighbours sets specific cells neighbour count") {
		int x = 1;
		int y = 1;
		int neighbours = 3;
		
		g.setCellNeighbours(x, y, neighbours);
		
		REQUIRE(g.getCellNeighbours(x, y) == neighbours);
	}
	
	SECTION("getFieldWidth returns default field width of 50") {
		REQUIRE(g.getFieldWidth() == GameField::DEFAULT_FIELD_SIZE);
	}
	
	SECTION("getFieldHeight returns default field height of 50") {
		REQUIRE(g.getFieldHeight() == GameField::DEFAULT_FIELD_SIZE);
	}
	
	SECTION("getRectangle returns rectangle with all measurements") {
		// default width and height are 549 
		// DEFAULT_FIELD_SIZE * (CELL_SIZE + 1) - 1
		// 			50				 10	
		
		int left = 0;
		int right = 549;
		int top = 0;
		int bottom = 549;
		int width = 549;
		int height = 549;	

		Rectangle r = g.getRectangle();
	
		REQUIRE(r.left == left);
		REQUIRE(r.right == right);
		REQUIRE(r.top == top);
		REQUIRE(r.bottom == bottom);
		REQUIRE(r.width == width);
		REQUIRE(r.height == height);
	}
	
	SECTION("getCellRectangle returns specific cells rectangle with all measurements") {
		int x = 0;
		int y = 0;
		
		int left = 0;
		int right = Cell::CELL_SIZE;
		int top = 0;
		int bottom = Cell::CELL_SIZE;
		int width = Cell::CELL_SIZE;
		int height = Cell::CELL_SIZE;	

		Rectangle r = c.getCellRectangle(x, y);
	
		REQUIRE(r.left == left);
		REQUIRE(r.right == right);
		REQUIRE(r.top == top);
		REQUIRE(r.bottom == bottom);
		REQUIRE(r.width == width);
		REQUIRE(r.height == height);
	}
	
	SECTION("cellShouldBeDrawn returns if a cell is within boundaries") {
		// right and bottom edge of cell at (1,1) is at 21p
		
		int x = 1; 
		int y = 1;
		
		int rightEdgeSmall = 20;
		int bottomEdgeSmall = 20;
		
		int rightEdgeLarge = 50;
		int bottomEdgeLarge = 50;
		
		REQUIRE(g.cellShouldBeDrawn(x, y, rightEdgeSmall, bottomEdgeSmall) == false);
		REQUIRE(g.cellShouldBeDrawn(x, y, rightEdgeLarge, bottomEdgeLarge) == true);
	}
	
	SECTION("resize changes the size of the gamefield") {
		
		int width;
		int height;
		
		GameField g;
		
		SECTION("default gamefield size is 50 by 50") {
			REQUIRE(g.getFieldWidth() == GameField::DEFAULT_FIELD_SIZE);
			REQUIRE(g.getFieldHeight() == GameField::DEFAULT_FIELD_SIZE);
		}
		
		SECTION("gamefield cannot exceed maximum size of 500 in any dimension") {
			width = GameField::MAX_FIELD_SIZE + 1;
			height = GameField::MAX_FIELD_SIZE + 1;

			g.resize(width, height);
			REQUIRE(g.getFieldWidth() == GameField::DEFAULT_FIELD_SIZE);
			REQUIRE(g.getFieldHeight() == GameField::DEFAULT_FIELD_SIZE);			
		}
		
		SECTION("gamefield can be reduced in size") {
			width = 10;
			height = 20; 
			
			g.resize(width, height);
			REQUIRE(g.getFieldWidth() == width);
			REQUIRE(g.getFieldHeight() == height);
		}
		
		SECTION("gamefield can be increased in size") {
			width = 200;
			height = 100; 
			
			g.resize(width, height);
			REQUIRE(g.getFieldWidth() == width);
			REQUIRE(g.getFieldHeight() == height);
		}			
	}
}
