void assignValues();

void generateLevel(int board[9][9], int difficulty, int level){

	if(difficulty==1){
		switch(level){
			case 1:
				assignValues(board,
					1,4,2,0,9,0,0,0,5, 7,0,0,4,0,0,0,8,9, 8,0,5,0,0,0,0,2,4,
					2,0,0,0,0,4,8,0,0, 0,3,0,0,0,1,2,6,0, 0,8,0,0,7,2,9,4,1,
					0,5,0,2,0,6,0,0,0, 0,2,8,0,0,9,4,1,0, 0,7,9,1,0,8,5,3,0
				);
				break;
			case 2:
				assignValues(board,
					1,0,0,0,9,4,7,0,5, 5,7,3,1,0,2,0,0,0, 0,4,0,0,5,3,1,0,8,
					0,8,1,5,6,7,3,4,0, 0,0,0,8,0,1,0,0,7, 0,5,6,4,0,9,0,0,2,
					4,6,0,0,0,0,0,9,0, 0,3,0,9,1,0,0,7,6, 9,0,0,0,4,0,0,0,0
				);
				break;
			case 3:
				assignValues(board,
					4,0,7,0,9,1,0,2,8, 0,9,8,0,4,0,5,0,0, 6,0,0,0,0,5,0,0,0,
					9,0,0,8,0,2,1,0,0, 0,0,0,0,0,6,2,4,3, 7,0,0,0,2,4,9,8,6,
					0,1,4,0,6,8,0,0,2, 5,0,2,0,0,0,8,0,0, 8,7,0,0,2,3,6,1,0
				);
				break;
			case 4:
				assignValues(board,
					5,6,0,4,9,8,0,0,2, 0,4,0,1,0,2,6,5,0, 0,0,1,0,0,0,0,8,4,
					0,0,4,6,0,9,2,1,5, 0,2,0,3,0,0,0,0,8, 8,9,0,0,1,0,3,4,6,
					0,8,3,7,5,0,0,2,0, 0,0,2,9,0,0,8,0,1, 0,1,0,0,0,0,5,0,0
				);
				break;
			case 5:
				assignValues(board,
					8,1,4,0,7,0,6,9,5, 0,0,2,1,6,0,3,0,0, 0,0,0,0,0,5,0,1,0,
					1,0,5,9,3,0,0,0,4, 0,0,8,6,2,0,0,0,3, 9,0,3,4,0,0,0,8,6,
					3,0,0,2,0,9,5,6,0, 0,0,0,0,0,0,8,0,0, 7,8,6,0,0,3,2,4,9
				);
				break;
			case 6:
				assignValues(board,
					0,0,5,0,4,0,1,0,8, 4,6,0,0,2,0,7,9,0, 7,0,0,3,1,6,0,0,0,
					5,3,6,7,0,1,9,0,2, 0,0,8,4,0,0,0,0,7, 2,0,7,0,9,0,0,0,0,
					6,0,2,1,5,4,0,3,0, 0,0,0,2,0,0,0,0,6, 9,0,3,0,7,8,2,1,0
				);
				break;
			case 7:
				assignValues(board,
					0,9,4,0,5,7,0,0,0, 2,0,0,0,0,0,0,3,0, 0,0,7,0,0,2,0,0,0,
					0,6,0,8,2,3,5,7,1, 0,7,3,5,9,1,2,0,6, 0,2,5,4,0,0,3,0,9,
					9,0,1,0,3,0,4,6,7, 0,4,2,0,0,5,0,1,0, 3,8,6,0,0,0,0,0,0
				);
				break;
			case 8:
				assignValues(board,
					9,5,0,4,0,2,8,3,0, 6,4,3,8,0,7,0,0,0, 0,2,0,0,6,0,7,0,5,
					3,8,0,0,7,0,0,0,9, 0,9,5,0,2,8,4,6,7, 0,0,4,0,9,0,3,0,8,
					2,0,0,0,0,0,0,5,0, 0,0,8,2,4,6,9,7,0, 0,0,0,0,3,0,2,0,0
				);
				break;
			case 9:
				assignValues(board,
					0,8,0,0,0,0,7,9,3, 0,1,0,9,8,5,0,0,0, 0,6,0,0,7,0,0,1,0,
					0,4,0,7,2,0,3,6,0, 3,5,0,8,0,0,1,7,0, 0,0,7,3,0,1,0,8,0,
					1,0,0,4,6,7,8,0,9, 5,9,0,0,3,0,0,2,0, 0,7,0,5,0,0,6,3,1
				);
				break;
			case 10:
				assignValues(board,
					6,0,0,0,5,0,7,2,3, 7,0,0,1,2,6,0,0,9, 2,0,5,0,4,3,0,0,6,
					0,6,1,2,0,4,0,7,5, 0,2,7,0,0,0,3,9,4, 0,0,0,0,8,7,2,0,0,
					0,7,6,0,0,0,0,0,0, 1,0,0,8,0,0,6,5,7, 9,3,0,0,7,5,0,0,0
				);
				break;
		}
	}else if(difficulty==2){
		switch(level){
			case 1:
				assignValues(board,
					0,0,1,0,0,0,9,4,0, 4,0,7,8,3,0,2,1,0, 9,0,6,5,0,0,8,0,3,
					8,0,0,6,0,0,0,0,0, 0,0,0,0,2,0,1,3,0, 0,0,0,0,0,3,5,0,0,
					5,7,0,0,0,2,4,8,0, 1,6,0,0,9,0,0,5,0, 0,0,0,4,1,0,0,0,7,
				);
				break;
			case 2:
				assignValues(board,
					0,7,4,0,0,9,5,0,0, 1,0,0,0,7,0,8,3,4, 3,0,2,0,0,4,0,0,1,
					0,0,1,9,4,0,6,7,5, 0,8,6,3,1,0,0,0,0, 0,0,7,5,0,0,0,0,3,
					0,2,0,0,6,3,0,0,0, 0,0,0,2,0,5,0,0,0, 0,9,0,0,0,0,4,0,0,
				);
				break;
			case 3:
				assignValues(board,
					0,7,0,4,0,8,9,3,2, 0,0,0,0,0,3,0,0,0, 8,9,0,2,0,0,7,4,0,
					9,6,0,0,0,0,2,0,0, 0,1,4,0,0,5,0,0,0, 0,0,7,0,0,2,8,9,0,
					0,0,0,0,8,0,5,2,1, 0,5,0,0,0,9,0,8,3, 0,8,0,0,2,0,0,7,0,
				);
				break;
			case 4:
				assignValues(board,
					1,0,0,0,0,0,0,8,2, 6,0,0,4,0,0,0,0,0, 0,9,0,7,1,0,0,0,0,
					3,0,7,0,0,0,4,0,0, 0,2,0,0,0,8,3,0,9, 0,0,9,0,7,1,0,6,5,
					0,0,4,2,9,0,5,0,6, 9,0,0,0,3,0,0,0,7, 7,3,0,8,0,5,0,0,1,
				);
				break;
			case 5:
				assignValues(board,
					1,5,7,3,0,8,0,0,0, 0,0,4,0,0,0,1,7,0, 0,0,0,0,1,7,0,6,0,
					0,4,3,2,0,1,7,0,9, 0,0,8,6,7,0,0,0,1, 0,0,0,9,0,0,6,0,8,
					7,1,0,0,0,0,3,2,0, 0,0,0,1,0,0,0,0,7, 0,0,6,0,0,3,0,0,4,
				);
				break;
			case 6:
				assignValues(board,
					4,0,9,0,0,1,0,0,0, 0,0,0,0,6,0,8,2,0, 8,0,0,0,7,9,0,4,3,
					0,0,0,6,0,0,0,0,4, 0,0,3,1,0,4,0,0,0, 5,4,7,0,0,0,0,0,0,
					9,0,6,2,3,5,0,7,0, 0,2,4,7,0,8,0,0,0, 1,0,5,0,4,0,0,0,8,
				);
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
		}
	}else if(difficulty==3){

	}
}

void assignValues(int board[9][9],
	int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
	int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9,
	int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8, int c9,
	int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8, int d9,
	int e1, int e2, int e3, int e4, int e5, int e6, int e7, int e8, int e9,
	int f1, int f2, int f3, int f4, int f5, int f6, int f7, int f8, int f9,
	int g1, int g2, int g3, int g4, int g5, int g6, int g7, int g8, int g9,
	int h1, int h2, int h3, int h4, int h5, int h6, int h7, int h8, int h9,
	int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9
){
	board[0][0] = a1;
	board[0][1] = a2;
	board[0][2] = a3;
	board[0][3] = a4;
	board[0][4] = a5;
	board[0][5] = a6;
	board[0][6] = a7;
	board[0][7] = a8;
	board[0][8] = a9;

	board[1][0] = b1;
	board[1][1] = b2;
	board[1][2] = b3;
	board[1][3] = b4;
	board[1][4] = b5;
	board[1][5] = b6;
	board[1][6] = b7;
	board[1][7] = b8;
	board[1][8] = b9;

	board[2][0] = c1;
	board[2][1] = c2;
	board[2][2] = c3;
	board[2][3] = c4;
	board[2][4] = c5;
	board[2][5] = c6;
	board[2][6] = c7;
	board[2][7] = c8;
	board[2][8] = c9;

	board[3][0] = d1;
	board[3][1] = d2;
	board[3][2] = d3;
	board[3][3] = d4;
	board[3][4] = d5;
	board[3][5] = d6;
	board[3][6] = d7;
	board[3][7] = d8;
	board[3][8] = d9;

	board[4][0] = e1;
	board[4][1] = e2;
	board[4][2] = e3;
	board[4][3] = e4;
	board[4][4] = e5;
	board[4][5] = e6;
	board[4][6] = e7;
	board[4][7] = e8;
	board[4][8] = e9;

	board[5][0] = f1;
	board[5][1] = f2;
	board[5][2] = f3;
	board[5][3] = f4;
	board[5][4] = f5;
	board[5][5] = f6;
	board[5][6] = f7;
	board[5][7] = f8;
	board[5][8] = f9;

	board[6][0] = g1;
	board[6][1] = g2;
	board[6][2] = g3;
	board[6][3] = g4;
	board[6][4] = g5;
	board[6][5] = g6;
	board[6][6] = g7;
	board[6][7] = g8;
	board[6][8] = g9;

	board[7][0] = h1;
	board[7][1] = h2;
	board[7][2] = h3;
	board[7][3] = h4;
	board[7][4] = h5;
	board[7][5] = h6;
	board[7][6] = h7;
	board[7][7] = h8;
	board[7][8] = h9;

	board[8][0] = i1;
	board[8][1] = i2;
	board[8][2] = i3;
	board[8][3] = i4;
	board[8][4] = i5;
	board[8][5] = i6;
	board[8][6] = i7;
	board[8][7] = i8;
	board[8][8] = i9;
}