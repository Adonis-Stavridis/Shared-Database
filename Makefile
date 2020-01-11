SHELL = /bin/bash
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -pthread
TERMINAL = gnome-terminal

OBJ = obj/
BIN = bin/
SRC = src/
INCLUDE = include/
BDD = bdd/
APPLI = appli/
S_ACCES = s_acces/
S_DATA = s_data/

AGE = age
GENDER = gender

P_APPLI1 = 5000
P_APPLI2 = 5001
P_DATA_AGE1 = 5002
P_DATA_AGE2 = 5003
P_DATA_GENDER1 = 5004
P_DATA_GENDER2 = 5005

SLEEP = 5
SLEEP_SYNC = 30

CODE_APPLI = $(wildcard $(SRC)$(APPLI)*.c)
OBJET_APPLI = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(CODE_APPLI))
CODE_S_ACCES = $(wildcard $(SRC)$(S_ACCES)*.c)
OBJET_S_ACCES = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(CODE_S_ACCES))
CODE_S_DATA = $(wildcard $(SRC)$(S_DATA)*.c)
OBJET_S_DATA = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(CODE_S_DATA))

EXEC_APPLI = appli
EXEC_S_ACCES = s_acces
EXEC_S_DATA = s_data

vpath %.c src
vpath %.o obj
vpath %.h include
vpath appli bin
vpath s_acces bin
vpath s_data bin

.PHONY: all clean

all: $(BIN)$(EXEC_APPLI) $(BIN)$(EXEC_S_ACCES) $(BIN)$(EXEC_S_DATA)

$(BIN)$(EXEC_APPLI) : $(OBJET_APPLI)
	@echo -e "\e[1m\e[36m----- Creating $@\e[0m\e[39m"
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ)$(APPLI)$(EXEC_APPLI).o : $(SRC)$(APPLI)$(EXEC_APPLI).c
	@echo -e "\e[1m\e[36m----- Compiling $@\e[0m\e[39m"
	@mkdir -p $(OBJ)$(APPLI)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c  $< -o $@

$(OBJ)$(APPLI)%.o : $(SRC)$(APPLI)%.c $(INCLUDE)%.h
	@echo -e "\e[1m\e[36m----- Compiling $@\e[0m\e[39m"
	@mkdir -p $(OBJ)$(APPLI)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(BIN)$(EXEC_S_ACCES) : $(OBJET_S_ACCES)
	@echo -e "\e[1m\e[36m----- Creating $@\e[0m\e[39m"
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ)$(S_ACCES)$(EXEC_S_ACCES).o : $(SRC)$(S_ACCES)$(EXEC_S_ACCES).c
	@echo -e "\e[1m\e[36m----- Compiling $@\e[0m\e[39m"
	@mkdir -p $(OBJ)$(S_ACCES)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c  $< -o $@

$(OBJ)$(S_ACCES)%.o : $(SRC)$(S_ACCES)%.c $(INCLUDE)%.h
	@echo -e "\e[1m\e[36m----- Compiling $@\e[0m\e[39m"
	@mkdir -p $(OBJ)$(S_ACCES)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(BIN)$(EXEC_S_DATA) : $(OBJET_S_DATA)
	@echo -e "\e[1m\e[36m----- Creating $@\e[0m\e[39m"
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ)$(S_DATA)$(EXEC_S_DATA).o : $(SRC)$(S_DATA)$(EXEC_S_DATA).c
	@echo -e "\e[1m\e[36m----- Compiling $@\e[0m\e[39m"
	@mkdir -p $(OBJ)$(S_DATA)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c  $< -o $@

$(OBJ)$(S_DATA)%.o : $(SRC)$(S_DATA)%.c $(INCLUDE)%.h
	@echo -e "\e[1m\e[36m----- Compiling $@\e[0m\e[39m"
	@mkdir -p $(OBJ)$(S_DATA)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

test_simple:
	@echo -e "\e[1m\e[36m----- Creating terminals\e[0m\e[39m"
	@$(TERMINAL) -e "make t_s_acces" --geometry "65x60+700+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_s_data_age1" --geometry "65x16+2000+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_s_data_gender1" --geometry "65x16+2000+400"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_appli1" --geometry "65x60+0+0"> /dev/null 2>&1
	@sleep $(SLEEP_SYNC)
	@$(TERMINAL) -e "make t_s_data_age2" --geometry "65x16+2000+800"> /dev/null 2>&1

test_all:
	@echo -e "\e[1m\e[36m----- Creating terminals\e[0m\e[39m"
	@$(TERMINAL) -e "make t_s_acces" --geometry "65x60+700+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_s_data_age1" --geometry "65x12+2000+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_s_data_age2" --geometry "65x12+2000+275"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_s_data_gender1" --geometry "65x12+2000+550"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_s_data_gender2" --geometry "65x12+2000+825"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_appli1" --geometry "65x25+0+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make t_appli2" --geometry "65x25+0+550"> /dev/null 2>&1

t_appli1: $(BIN)$(EXEC_APPLI)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^ $(P_APPLI1)
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

t_appli2: $(BIN)$(EXEC_APPLI)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^ $(P_APPLI2)
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

t_s_acces: $(BIN)$(EXEC_S_ACCES)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

t_s_data_age1: $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^ $(P_DATA_AGE1) $(AGE)
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

t_s_data_age2: $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^ $(P_DATA_AGE2) $(AGE)
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

t_s_data_gender1: $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^ $(P_DATA_GENDER1) $(GENDER)
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

t_s_data_gender2: $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[31m----- Start of test\e[0m\e[39m"
	@./$^ $(P_DATA_GENDER2) $(GENDER)
	@echo -e "\e[1m\e[31m----- End of test\e[0m\e[39m"

mem_simple:
	@echo -e "\e[1m\e[36m----- Creating terminals\e[0m\e[39m"
	@$(TERMINAL) -e "make mem_s_acces" --geometry "65x60+700+0"> /dev/null 2>&1
	@sleep 1
	@$(TERMINAL) -e "make mem_s_data_age1" --geometry "65x16+2000+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_s_data_gender1" --geometry "65x16+2000+400"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_appli1" --geometry "65x60+0+0"> /dev/null 2>&1
	@sleep $(SLEEP_SYNC)
	@$(TERMINAL) -e "make mem_s_data_age2" --geometry "65x16+2000+800"> /dev/null 2>&1

mem_all:
	@echo -e "\e[1m\e[36m----- Creating terminals\e[0m\e[39m"
	@$(TERMINAL) -e "make mem_s_acces" --geometry "65x60+700+0"> /dev/null 2>&1
	@sleep 1
	@$(TERMINAL) -e "make mem_s_data_age1" --geometry "65x12+2000+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_s_data_age2" --geometry "65x12+2000+275"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_s_data_gender1" --geometry "65x12+2000+550"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_s_data_gender2" --geometry "65x12+2000+825"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_appli1" --geometry "65x25+0+0"> /dev/null 2>&1
	@$(TERMINAL) -e "make mem_appli2" --geometry "65x25+0+550"> /dev/null 2>&1

mem_appli1 : $(BIN)$(EXEC_APPLI)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^ $(P_APPLI1)
	@sleep $(SLEEP)

mem_appli2 : $(BIN)$(EXEC_APPLI)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^ $(P_APPLI2)
	@sleep $(SLEEP)

mem_s_acces : $(BIN)$(EXEC_S_ACCES)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^
	@sleep $(SLEEP)

mem_s_data_age1 : $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^ $(P_DATA_AGE1) $(AGE)
	@sleep $(SLEEP)

mem_s_data_age2 : $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^ $(P_DATA_AGE2) $(AGE)
	@sleep $(SLEEP)

mem_s_data_gender1 : $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^ $(P_DATA_GENDER1) $(GENDER)
	@sleep $(SLEEP)

mem_s_data_gender2 : $(BIN)$(EXEC_S_DATA)
	@echo -e "\e[1m\e[33m----- Verifying memory\e[0m\e[39m"
	@valgrind --leak-check=full --track-origins=yes --error-exitcode=1 $^ $(P_DATA_GENDER2) $(GENDER)
	@sleep $(SLEEP)

archive :
	@echo -e "\e[1m\e[32m----- Creating archive\e[0m\e[39m"
	@tar -czf archive.tar.gz README.md Rapport.pdf Makefile $(SRC) $(INCLUDE) $(BDD)

clean :
	@echo -e "\e[1m\e[32m----- Deleting\e[0m\e[39m"
	@rm -rf $(BIN) $(OBJ)
