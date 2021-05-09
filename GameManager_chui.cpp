#include "GameManager.h"
#include <sstream>

GameManager::GameManager()
{
	// 先假定都是人類玩家
	this->current_player = 0; // 先假定player1先手
	this->players[0] = new HumanPlayer(true);
	this->players[1] = new HumanPlayer(false);
}
void GameManager::game()
{
	Board chessBoard;
	Viewer viewer;
    string command, type;

    showMenu();
	
    bool endGame = false;
    while (1)
    {
        // white turn
        bool validInput = false;
        do
        {
            cout << "Now is WHITE turn!\n" << endl;
            viewer.showBoard(chessBoard);
            getline(cin, command);

            stringstream ss(command); // 切割字串用
            ss >> type;
            if (type == "move" || type == "Move") // 移動 (ex: move 0 0 0 2)
            {
                Position moveToPos, moveFromPos;
                ss >> moveFromPos.x >> moveFromPos.y >> moveToPos.x >> moveToPos.y;

                if (chessBoard.board[moveFromPos.y][moveFromPos.x].piece.type == -1) // 從空的格子移動
                {
                    cout << "請選擇正確的位置！" << endl;
                    system("pause");
                }
                else if (chessBoard.board[moveFromPos.y][moveFromPos.x].piece.isWhiteSide != players[current_player]->isWhiteSide) // 移動不屬於自己的棋子
                {
                    cout << "請選擇正確的棋子!" << endl;
                    system("pause");
                }
                else if (invalidMove(moveFromPos, moveToPos, chessBoard.board[moveFromPos.y][moveToPos.x].piece.type, chessBoard)) // 移動模式不符合棋種
                {
                    //條件要改成如果函式是回傳false，則輸入不合法
                    //多傳chessboard進去
                    cout << "輸入違規" << endl;
                }
                else // 正常情況
                {
                    players[current_player]->OnMove(chessBoard, moveFromPos, moveToPos); // 移動
                    system("pause");
                    validInput = true;
                }
            }
            else if (type == "exit" || type == "Exit") // 投降
            {
                endGame = true;
                break;
            }
            system("cls"); // 清空畫面
        } while (!validInput); // 正確輸入，才離開迴圈


        if (endGame) break; // 判斷要不要離開遊戲
        current_player = (current_player == 0) ? 1 : 0; // 切換玩家

        // black turn
        validInput = false;
        do
        {
            cout << "Now is BLACK turn!\n" << endl;
            viewer.showBoard(chessBoard);
            getline(cin, command);

            stringstream ss;
            ss << command;
            ss >> type;
            if (type == "move" || type == "Move") // 移動
            {
                Position moveToPos, moveFromPos;
                ss >> moveFromPos.x >> moveFromPos.y >> moveToPos.x >> moveToPos.y;

                if (chessBoard.board[moveFromPos.y][moveFromPos.x].piece.type == -1) // 從空的格子移動
                {
                    cout << "請選擇正確的位置！" << endl;
                    system("pause");
                }
                else if (chessBoard.board[moveFromPos.y][moveFromPos.x].piece.isWhiteSide != players[current_player]->isWhiteSide)
                {
                    cout << "請選擇正確的棋子!" << endl;
                    system("pause");
                }
                else
                {
                    players[current_player]->OnMove(chessBoard, moveFromPos, moveToPos);
                    validInput = true;
                }

            }
            else if (type == "exit" || type == "Exit") // 投降
            {
                endGame = true;
                break;
            }
            else
            {

            }
            system("cls");
        } while (!validInput);


        if (endGame) break;
        current_player = (current_player == 0) ? 1 : 0;

    }
	// loop:
	// 先手下旗
	// 判斷
	// 後手下旗
	// 判斷

	// 遊戲結束
	// 要不要再來一局?
}
void GameManager::showMenu()
{
    // 隨便從網路上抓的示意圖，之後可以改掉
    cout << "********************************************************************************\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*        ******     **                                                         *\n";
    cout << "*      **********   **                                                         *\n";
    cout << "*    ***            **                                                         *\n";
    cout << "*   ***             **            ****       ****        ****                  *\n";
    cout << "*   ***             **          ********   ***  ***    ***  ***                *\n";
    cout << "*   ***             ** ****    ***    *** ***         ***                      *\n";
    cout << "*   ***             ****  **   **********   ******      ******                 *\n";
    cout << "*    ***            ***    **  ***             *****       *****               *\n";
    cout << "*      **********   **     **   ****       ***   **    ***   **                *\n";
    cout << "*       *******     **     **     ****       *****       *****                 *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                        ' welcome to chess game '                             *\n";
    cout << "*                                                                              *\n";
    cout << "*                         press enter to continue.                             *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                              *\n";
    cout << "*                                                                          v1.0*\n";
    cout << "********************************************************************************\n";
    system("pause");
    system("cls");
	// show menu
	//  -美化或發揮創意的介面
	//  -可以放個分組名單?
	// 依據使用者輸入，選擇:
	// l) play new game
	// 2) load game
	// 3) 我不知道
}
bool GameManager::invalidMove(Position moveFromPos, Position moveToPos, int type, Board chessBoard)
{
    //判斷移動格數是否合法
    
    //除了馬，全部都要思考有沒有越過其他棋子的問題
    if (type != 5) // knight
    {
        int min_x = moveFromPos.x;
        int max_x = moveToPos.x;
        if (moveToPos.x < min_x) {
            min_x = moveToPos.x;
            max_x = moveFromPos.x;
        }
        int min_y = moveFromPos.y;
        int max_y = moveToPos.x;
        if (moveToPos.y < min_y) {
            min_y = moveToPos.y;
            max_y = moveFromPos.y;
        }
        int j = min_y;

        //判斷直線橫線或是斜線
        if (abs(moveToPos.x - moveFromPos.x) != 0) {
            if (abs(moveToPos.y - moveFromPos.y) != 0) {
                //斜的
                for (int i = min_x;i <= max_x;i++) {
                    if (chessBoard.board[j++][i].piece.type != -1) {
                        return false;
                    }
                }
            }
            else {
                //橫的
                for (int i = min_x;i <= max_x;i++) {
                    if (chessBoard.board[j][i].piece.type != -1) {
                        return false;
                    }
                }
            }
        }
        else {
            if (abs(moveToPos.y - moveFromPos.y) != 0) {
                //直的
                for (int i = min_y;i <= max_y;i++) {
                    if (chessBoard.board[i][min_x].piece.type != -1) {
                        return false;
                    }
                }
            }
            else {
                //To From 同一點
            }
        }
    }
    if (type == 1) // king
    {
        if (abs(moveToPos.x - moveFromPos.x) <= 1) {
            if (abs(moveToPos.y - moveFromPos.y <= 1)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else if (type == 2) // queen
    {
        //走斜的 delta x == delta y
        //走直的 delta y != 0, delta x == 0 
        //走橫的 delta x != 0, delta y == 0
        if (abs(moveToPos.x - moveFromPos.x) == abs(moveToPos.y - moveFromPos.y)) {
            return true;
        }
        else if ((moveToPos.x - moveFromPos.x) != 0 && (moveToPos.y - moveFromPos.y) == 0) {
            return true;
        }
        else if ((moveToPos.y - moveFromPos.y) != 0 && (moveToPos.x - moveFromPos.x) == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (type == 3) // rook
    {
        //走橫的 delta x != 0, delta y == 0
        if ((moveToPos.x - moveFromPos.x) != 0 && (moveToPos.y - moveFromPos.y) == 0) {
            return true;
        }
        //走直的 delta y != 0, delta x == 0 
        else if ((moveToPos.y - moveFromPos.y) != 0 && (moveToPos.x - moveFromPos.x) == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (type == 4) // bishop
    {
        //走斜的 delta x == delta y 
        if (abs(moveToPos.x - moveFromPos.x) == abs(moveToPos.y - moveFromPos.y)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (type == 5) // knight
    {
        //看不懂維基百科...
        //若8個位置中王佔據其中一個，則可構成將軍，自己的國王死??
        //走日字 delta y = +-2, delta x = +-1
        //delta y = +-1, delta x = +-2
        if (abs(moveToPos.x - moveFromPos.x) == 1 && abs(moveToPos.y - moveFromPos.y) == 2) {
            return true;
        }
        else if (abs(moveToPos.x - moveFromPos.x) == 2 && abs(moveToPos.y - moveFromPos.y) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (type == 6) // pawn
    {
        //第一次可以往前走兩格，所以判斷如果士兵原本在y == 6||y == 1，知道是第一次移動
        //第二次開始只能往前走一格，除非斜前方有對方棋子可以走斜的把對方吃掉，多傳入參數知道斜前方有沒有敵對棋子
        if ((moveToPos.y - moveFromPos.y) == -1) {
            if (moveToPos.x - moveFromPos.x == 0) {
                return true;
            }
            else if (abs(moveToPos.x - moveFromPos.x) == 1) {
                if (chessBoard.board[moveToPos.y][moveToPos.y].piece.isWhiteSide != chessBoard.board[moveFromPos.y][moveFromPos.y].piece.isWhiteSide) {
                    //敵對棋子
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if ((moveToPos.y - moveFromPos.y) == -2) {
            if (moveFromPos.y == 6) { // ->iswhite == true
                return true;
            }
            else if (moveFromPos.y == 1) { // ->iswhite == false
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    //promote
    //castling
    //Passant Capturing
    return false;
}
