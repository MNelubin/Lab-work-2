PROJECT = card_app

LIBPROJECT = $(PROJECT).a

TESTPROJECT = test-$(PROJECT)

CXX = g++

A = ar

AFLAGS = rsv

CCXFLAGS = -I. -std=c++17 -Wall -g -fPIC -Werror -Wpedantic -Wall -Iinclude

LDXXFLAGS = $(CCXFLAGS) -L. -l:$(LIBPROJECT)

LDGTESTFLAGS = $(LDXXFLAGS) -lgtest -lgtest_main -lpthread

INC_DIR = include

DEPS=$(wildcard $(INC_DIR)/*.h)

SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.cpp) \
      $(wildcard $(SRC_DIR)/cards/*.cpp) \
      $(wildcard $(SRC_DIR)/player/*.cpp)

OBJ = $(SRC:.cpp=.o)

#OBJ = card.o spell_card.o attack_spell_card.o heal_spell_card.o buff_spell_card.o defence_spell_card.o beast_card.o creature_card.o weapon_card.o artifact_card.o shield_card.o buff_card.o hand.o

TEST_DIR = tests

TEST_OBJ = test-card.o

.PHONY: default

default: all

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(LIBPROJECT): $(OBJ)
	$(A) $(AFLAGS) $@ $^

$(PROJECT): main.o $(LIBPROJECT)
	$(CXX) -o $@ main.o $(LDXXFLAGS)

$(TESTPROJECT): $(LIBPROJECT) $(TEST_OBJ)
	$(CXX) -o tests/unit_tests tests/test-card.cpp $(SRC) $(LDGTESTFLAGS)

test: $(TESTPROJECT)

all: $(PROJECT)

.PHONY: clean

clean:
	rm -f *.o

cleanall: clean
	rm -f $(PROJECT) $(LIBPROJECT) $(TESTPROJECT)

