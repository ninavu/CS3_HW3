all:
	g++ --std=c++14 -Wall TimeCode.cpp TimeCodeTests.cpp -o tc
	g++ --std=c++14 -Wall TimeCode.cpp NASALaunchAnalysis.cpp -o nasa
	g++ --std=c++14 -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt
