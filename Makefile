clientmain:readXmlFile.o client.o clientmain.o synLink.o
	gcc -o clientmain clientmain.o client.o readXmlFile.o synLink.o -lpthread -lxml2
clientmain.o:clientmain.c
	gcc -c clientmain.c
client.o:client.c 
	gcc -c client.c -lpthread
readXmlFile.o:readXmlFile.c
	gcc -c readXmlFile.c -I /usr/include/libxml2
synLink.o:synLink.c
	gcc -c synLink.c 
clean:
	rm clientmain client.o readXmlFile.o
