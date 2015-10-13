Read Me


(A)    Using the windows7 operator system,and compile the program on Dec-Cpp platform.If you can use the Dev-Cpp, open the Dev-Cpp and click file->open project or file->choose the existed C source code.
      If you are the first time to use Dev-Cpp,click tools->complier options->directions,and then add the absolute path C:\MinGW\bin to Binaries,pop it at the first position;add the absolute path C:\MinGW\lib to libraries,pop it at the first position;add the absolute path C:\MinGW\include to C Includes,pop it at the first position(You may have a different path to install the MinGW,using your own path,the "C:\MinGW\" just an example)
	Put the read_map.h and other two C source code in a same folder.
      Click execute->compile&run.After the compiling,the commander window will comes out and then you need to input some code to run the program.


(B)    After the commander window comes out, you can input the absolute path of the file(include the name of the file and .txt,and when you input ¡°\¡±,you should change to ¡°\\¡±).
      Then,input the origin and destination place.You will get indication while you input the street name and house number.If the street or the house number is incorrect,the program will report such an error.
	After you finish the input,the program will give you the result.For the Dijkstra algorithm,you will get at least one shortest path.For the Greedy algorithm,maybe the program will give you a shortest path or just a path to the destination which is not the shortest one or just output "can not find the destination".
¡¡¡¡
(C)Output of each algorithm for each input data set
All the following input will be same to both of the algorithms.

1.Using melbourne map:
Example 1
For algorithm Dijkstra :
input the name of the file:melbourne.txt
input the start street name:Eber
input the start house number:2000
input the destination street name:Henry
input the destination house number:7000
the coordinate of start is:x=20,y=10
the coordinate of destination is:x=10,y=25
/---------------------Next Path-------------------/
Head North on Hollywood.
go to the vertex 20 16 in 0.6 miles.And then turn left!onto Wingate
go to the vertex 10 18 in 1.1 miles and 158 foot.And then turn right!onto Minto
stop on street Henry,house number is 7000,in 0.7 miles.
    
For algorithm Greedy:(find the shortset path)
input the name of the file:melbourne.txt
input the start street name:Eber
input the start house number:2000
input the destination street name:Henry
input the destination house number:7000
the coordinate of start is:x=20,y=10
the coordinate of destination is:x=10,y=25
/---------------------Next Path-------------------/
Head North on Hollywood.
go to the vertex 20 16 in 0.6 miles.And then turn left!onto Wingate
go to the vertex 10 18 in 1.1 miles and 158 foot.And then turn right!onto Minton
stop on street Henry,house number is 7000,in 0.7 miles.

Example 2:
For algorithm Dijkstra :
input the name of the file:melbourne.txt
input the start street name:W New Haven
input the start house number:2000
input the destination street name:Eber
input the destination house number:1000
the coordinate of start is:x=20,y=30
the coordinate of destination is:x=30,y=10
/---------------------Next Path-------------------/
Head Eest on W New Haven.
go to the vertex 30 30 in 1.0 miles.And then turn right!onto Diary
stop on street Eber,house number is 1000,in 2.0 miles.
/---------------------Next Path-------------------/
Head South on Hollywood.
go to the vertex 20 10 in 2.0 miles.And then turn left!onto Eber
stop on street Eber,house number is 1000,in 1.0 miles.
/---------------------Next Path-------------------/
Head South on Hollywood.
go to the vertex 20 15 in 1.5 miles.And then turn left!onto Florida
go to the vertex 30 15 in 1.0 miles.And then turn right!onto Diary
stop on street Eber,house number is 1000,in 0.5 miles.

For algorithm Greedy:(can not find the path)
input the name of the file:melbourne.txt
input the start street name:W New Haven
input the start house number:2000
input the destination street name:Eber
input the destination house number:1000
the coordinate of start is:x=20,y=30
the coordinate of destination is:x=30,y=10
The algorithm can not find out the shortest way!!!!

Example 3:
For algorithm Dijkstra :
input the name of the file:melbourne.txt
input the start street name:Eber
input the start house number:2750
input the destination street name:Florida
input the destination house number:3800
the coordinate of start is:x=12.894737,y=10.000000
the coordinate of destination is:x=22.000000,y=15.000000
/---------------------Next Path-------------------/
Head Eest on Eber.
go to the vertex 20 10 in 0.7 miles and 55 foot.And then turn left!onto Hollywood
go to the vertex 20 15 in 0.5 miles.And then turn right!onto Florida
stop on street Florida,house number is 3800,in 0.2 miles.

For algorithm Greedy:(not the shortest path)
input the name of the file:melbourne.txt
input the start street name:Eber
input the start house number:2750
input the destination street name:Florida
input the destination house number:3800
the coordinate of start is:x=12.894737,y=10.000000
the coordinate of destination is:x=22.000000,y=15.000000
/---------------------Next Path-------------------/
Head West on Eber.
go to the vertex 10 11 in 0.3 miles and 163 foot.And then turn right!onto Minton
go to the vertex 10 18 in 0.7 miles.And then turn right!onto Wingate
go to the vertex 20 16 in 1.1 miles and 158 foot.And then turn right!onto Hollywood
go to the vertex 20 15 in 0.1 miles.And then turn left!onto Florida
stop on street Florida,house number is 3800,in 0.2 miles.


2.Using NewYork map:
For algorithm Dijkstra :
input the name of the file:NewYork.txt
input the start street name:62nd Dr
input the start house number:9
input the destination street name:63rd Ave
input the destination house number:68
the coordinate of start is:x=29.600000,y=35.299999
the coordinate of destination is:x=56.200001,y=52.599998
/---------------------Next Path-------------------/
Head NorthEest on 62nd Dr.
go to the vertex 48 57 in 0.2 miles and 4 foot.And then turn right!onto Alderton
 St
go to the vertex 57 54 in 335 foot.And then turn right!onto 63rd Ave
stop on street 63rd Ave,house number is 68,in 57 foot.

For algorithm Greedy:(find the shortset path)
input the name of the file:NewYork.txt
input the start street name:62nd Dr
input the start house number:9
input the destination street name:63rd Ave
input the destination house number:68
the coordinate of start is:x=29.600000,y=35.299999
the coordinate of destination is:x=56.200001,y=52.599998
/---------------------Next Path-------------------/
Head NorthEest on 62nd Dr.
go to the vertex 48 57 in 0.2 miles and 4 foot.And then turn right!onto Alderton St
go to the vertex 57 54 in 335 foot.And then turn right!onto 63rd Ave
stop on street 63rd Ave,house number is 68,in 57 foot.

For algorithm Dijkstra :
input the name of the file:NewYork.txt
input the start street name:Woodhaven Blvd
input the start house number:40
input the destination street name:Ellwell Crescent
input the destination house number:98
the coordinate of start is:x=24.157894,y=49.684212
the coordinate of destination is:x=79,y=23
/---------------------Next Path-------------------/
Head SouthEast on Woodhaven Blvd.
go to the vertex 35 28 in 0.1 miles and 329 foot.And then turn left!onto 63rd Ave
go to the vertex 45 35 in 443 foot.And then turn right!onto Carlton St
stop on street Ellwell Crescent,house number is 98,in 0.2 miles and 219 foot.

For algorithm Greedy:(not the shortest path)
input the name of the file:NewYork.txt
input the start street name:Woodhaven Blvd
input the start house number:40
input the destination street name:Ellwell Crescent
input the destination house number:98
the coordinate of start is:x=24.157894,y=49.684212
the coordinate of destination is:x=79,y=23
/---------------------Next Path-------------------/
Head NorthWest on Woodhaven Blvd.
go to the vertex 13 79 in 0.2 miles and 57 foot.And then turn right!onto Eliot Ave
go to the vertex 20 83 in 285 foot.And then turn right!onto Austin St
go to the vertex 87 58 in 0.4 miles and 417 foot.And then turn right!onto 63rd Dr
go to the vertex 79 46 in 510 foot.And then turn left!onto Alderton St
go to the vertex 96 39 in 0.1 miles and 122 foot.And then turn right!onto Dieterle Crescent
go to the vertex 88 22 in 0.1 miles and 142 foot.And then turn right!onto Carlton St
stop on street Ellwell Crescent,house number is 98,in 320 foot.

For algorithm Dijkstra :
input the name of the file:NewYork.txt
input the start street name:Woodhaven Blvd
input the start house number:60
input the destination street name:63rd Dr
input the destination house number:20
the coordinate of start is:x=31,y=36
the coordinate of destination is:x=71,y=32
/---------------------Next Path-------------------/
Head SouthEast on Woodhaven Blvd.
go to the vertex 35 28 in 316 foot.And then turn left!onto 63rd Ave
go to the vertex 49 40 in 0.1 miles and 141 foot.And then turn right!onto Bourton St
stop on street 63rd Dr,house number is 20,in 0.1 miles and 300 foot.
/---------------------Next Path-------------------/
Head SouthEast on Woodhaven Blvd.
go to the vertex 35 28 in 316 foot.And then turn left!onto 63rd Ave
go to the vertex 45 35 in 443 foot.And then turn right!onto Carlton St
go to the vertex 67 27 in 0.1 miles and 300 foot.And then turn left!onto 63rd Dr
stop on street 63rd Dr,house number is 20,in 226 foot.

For algorithm Greedy:(can not find the path)
input the name of the file:NewYork.txt
input the start street name:Woodhaven Blvd
input the start house number:60
input the destination street name:63rd Dr
input the destination house number:20
the coordinate of start is:x=31,y=36
the coordinate of destination is:x=71,y=32
The algorithm can not find out the shortest way!!!!
	