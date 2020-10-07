
g++-10 -o dbscan dbscan.cpp `pkg-config --libs --cflags gtkmm-3.0`

./dbscan

rm -r ./dbscan