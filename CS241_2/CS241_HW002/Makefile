CXX = g++
CXXFLAGS = -std=c++11

gtushell: exception.o json.o os.o file.o regular-file.o directory-file.o shell.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

exception.o: exception.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

json.o: json.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

os.o: os.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

file.o: file.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

regular-file.o: regular-file.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

directory-file.o: directory-file.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

shell.o: shell.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o gtushell

.PHONY: run
run: gtushell
	./gtushell
