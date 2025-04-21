# Created by: Nasseef Abukamail
# This Makefile will run tests for the appointment class
# The tests will run automatically using GitHub Actions
# This is to test continuous integration (CI).
#
#Variables
CC = g++
CFLAGS = -g -Wall -std=c++11

# Linking all the files and run the tests. Use your own header and
# object files.

a.out: appointment.o appointment.h appointment_main.o
	$(CC) $(CFLAGS) _TEST/appointment.o _TEST/appointment_main.o -o a.out

appointment.o: appointment.cc appointment.h
	$(CC) -c $(CFLAGS) appointment.cc -o _TEST/appointment.o

appointment_main.o: appointment_main.cc appointment.h
	$(CC) -c $(CFLAGS) appointment_main.cc -o _TEST/appointment_main.o

######################################### R U N   T E S T s ##################################################
run_tests: appointment.h appointment.o appointment_main.o
	head appointment.cc
	$(CC) $(CFLAGS) _TEST/TEST_cases.cc _TEST/appointment.o -o _TEST/a.out && ./_TEST/a.out -sr compact
	$(CC) $(CFLAGS) _TEST/appointment.o _TEST/appointment_main.o -o _TEST/a.out
	sh _TEST/run_tests.sh
##############################################################################################################

clean:
	rm -rf _TEST/*.o _TEST/run_tests a.out _TEST/a.out