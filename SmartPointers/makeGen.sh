for i in $(seq 1 15)
do
	echo "test$i: tests/test$i.cpp Graph.h
	$(CC) $(CFLAGS) tests/test$i.cpp -o test$i
	" >> tmp
done
