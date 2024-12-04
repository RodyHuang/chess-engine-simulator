chess: ChessMain.o Bishop.o King.o Pawn.o Queen.o Rook.o ChessPiece.o Knight.o Position.o ChessGame.o
	g++ -g ChessMain.o Bishop.o King.o Pawn.o Queen.o Rook.o ChessPiece.o Knight.o Position.o ChessGame.o -o chess

ChessMain.o: ChessMain.cpp ChessGame.h ChessPiece.h Bishop.h King.h Pawn.h Queen.h Rook.h Knight.h Position.h Color.h
	g++ -Wall -g -c ChessMain.cpp

ChessGame.o: ChessGame.cpp ChessGame.h ChessPiece.h Bishop.h King.h Pawn.h Queen.h Rook.h Knight.h Position.h Color.h
	g++ -Wall -g -c ChessGame.cpp

Bishop.o: Bishop.cpp Bishop.h ChessPiece.h Position.h
	g++ -Wall -g -c Bishop.cpp

King.o: King.cpp King.h ChessPiece.h Position.h
	g++ -Wall -g -c King.cpp

Pawn.o: Pawn.cpp Pawn.h ChessPiece.h Position.h
	g++ -Wall -g -c Pawn.cpp

Queen.o: Queen.cpp Queen.h ChessPiece.h Position.h
	g++ -Wall -g -c Queen.cpp

Rook.o: Rook.cpp Rook.h ChessPiece.h Position.h
	g++ -Wall -g -c Rook.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h Position.h Color.h
	g++ -Wall -g -c ChessPiece.cpp

Knight.o: Knight.cpp Knight.h ChessPiece.h Position.h
	g++ -Wall -g -c Knight.cpp

Position.o: Position.cpp Position.h
	g++ -Wall -g -c Position.cpp

clean:
	rm -f *.o chess
