#include <iostream>
#include <vector>


int best_move = 0;
std::vector<int> last_move ;
std::vector<int> last_p;
int player=1;
int q_k_w = 1;
int k_k_w = 1;
int castle= 1;
int q_k_b = 1;
int k_k_b = 1;
int castle_b= 1;
int board[8][8];
int pawn_table[8][8] = {
0,  0,  0,  0,  0,  0,  0,  0,
50, 50, 50, 50, 50, 50, 50, 50,
10, 10, 20, 30, 30, 20, 10, 10,
5,  5, 10, 25, 25, 10,  5,  5,
0,  0,  0, 20, 20,  0,  0,  0,
5, -5,-10,  0,  0,-10, -5,  5,
5, 10, 10,-20,-20, 10, 10,  5,
0,  0,  0,  0,  0,  0,  0,  0
};

int knight_table[8][8] = {
        {-50,-40,-30,-30,-30,-30,-40,-50},
        {-40,-20,  0,  0,  0,  0,-20,-40},
        {-30,  0, 10, 15, 15, 10,  0,-30},
        {-30,  5, 15, 20, 20, 15,  5,-30},
        {-30,  0, 15, 20, 20, 15,  0,-30},
        {-30,  5, 10, 15, 15, 10,  5,-30},
        {-40,-20,  0,  5,  5,  0,-20,-40},
        {-50,-40,-30,-30,-30,-30,-40,-50}
};

int bishop_table[8][8] = {
        -20, -10, -10, -10, -10, -10, -10, -20,
        -10, 0, 0, 0, 0, 0, 0, -10,
        -10, 0, 5, 10, 10, 5, 0, -10,
        -10, 5, 5, 10, 10, 5, 5, -10,
        -10, 0, 10, 10, 10, 10, 0, -10,
        -10, 10, 10, 10, 10, 10, 10, -10,
        -10, 5, 0, 0, 0, 0, 5, -10,
        -20, -10, -10, -10, -10, -10, -10, -20,
};

int rook_table[8][8] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        5, 10, 10, 10, 10, 10, 10, 5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        -5, 0, 0, 0, 0, 0, 0, -5,
        0, 0, 0, 5, 5, 0, 0, 0
};

int queen_table[8][8] = {
        -20, -10, -10, -5, -5, -10, -10, -20,
        -10, 0, 0, 0, 0, 0, 0, -10,
        -10, 0, 5, 5, 5, 5, 0, -10,
        -5, 0, 5, 5, 5, 5, 0, -5,
        0, 0, 5, 5, 5, 5, 0, -5,
        -10, 5, 5, 5, 5, 5, 0, -10,
        -10, 0, 5, 0, 0, 0, 0, -10,
        -20, -10, -10, -5, -5, -10, -10, -20
};

int king_table[8][8] = {
        -30, -40, -40, -50, -50, -40, -40, -30,
        -30, -40, -40, -50, -50, -40, -40, -30,
        -30, -40, -40, -50, -50, -40, -40, -30,
        -30, -40, -40, -50, -50, -40, -40, -30,
        -20, -30, -30, -40, -40, -30, -30, -20,
        -10, -20, -20, -20, -20, -20, -20, -10,
        20, 20, 0, 0, 0, 0, 20, 20,
        20, 30, 10, 0, 0, 10, 30, 20
};
void display()
{
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {
            if(board[i][j]==100)
            {
                std::cout << "K " ;
            }
            if(board[i][j]==1)
            {
                std::cout << "P " ;
            }
            if(board[i][j]==9)
            {
                std::cout << "Q " ;
            }
            if(board[i][j]==4)
            {
                std::cout << "B " ;
            }
            if(board[i][j]==3)
            {
                std::cout << "N " ;
            }
            if(board[i][j]==5)
            {
                std::cout << "R " ;
            }
            if(board[i][j]==-100)
            {
                std::cout << "K " ;
            }
            if(board[i][j]==-1)
            {
                std::cout << "p " ;
            }
            if(board[i][j]==-9)
            {
                std::cout << "q " ;
            }
            if(board[i][j]==-4)
            {
                std::cout << "b " ;
            }
            if(board[i][j]==-3)
            {
                std::cout << "n " ;
            }
            if(board[i][j]==-5)
            {
                std::cout << "r " ;
            }
            if(board[i][j]==0)
            {
                std::cout << ". " ;
            }

        }
        std::cout<< '\n';
    }

}
std::vector<int> legal_move_per_piece(int x,int y)
{
    int selected_peice = board[x][y];
    int legal_move = 0;
    std::vector<int> vec;
    if(selected_peice==1)
    {
        if(board[x-1][y]==0 && board[x-2][y]==0 && x==6)
        {
            legal_move = legal_move +2;
            vec.push_back((x-1)*10 + y);
            vec.push_back((x-2)*10 + y);
        }
        if (board[x-1][y]==0 && x!=6 )
        {
            legal_move = legal_move +1;
            vec.push_back((x-1)*10 + y);
        }
        if(y!=0 && y!=7)
        {
        if(board[x-1][y+1]<0 && board[x-1][y-1]<0 )
        {
            legal_move = legal_move +2;
            vec.push_back((x-1)*10 + (y+1));
            vec.push_back((x-1)*10 + (y-1));
        }
        if((board[x-1][y+1]<0 && (board[x-1][y-1]==0 || board[x-1][y-1]>0 )) || ((board[x-1][y+1]==0 || board[x-1][y+1]>0) && board[x-1][y-1]<0))
        {
            legal_move = legal_move +1;
            if(board[x-1][y+1]<0 && (board[x-1][y-1]==0 || board[x-1][y-1]>0 ))
            {
                vec.push_back((x-1)*10 + (y+1));
            }
            if(board[x-1][y-1]<0 && (board[x-1][y+1]==0 || board[x-1][y+1]>0)){
                vec.push_back((x-1)*10 + (y-1));
            }
        }
        }
        if(y==0){
            if(board[x-1][y+1]<0 )
            {
                legal_move = legal_move +1;
                vec.push_back((x-1)*10 + (y+1));
            }
        }
        if(y==7)
        {
            if(board[x-1][y-1]<0 )
            {
                legal_move = legal_move +1;
                vec.push_back((x-1)*10 + (y-1));
            }
        }

    }
    if(selected_peice==5)
    {
        int i=x+1;
        int j=y;
        if(i<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x-1;

        if(i>=0) {
            while (board[i][j] == 0 && (i < 8 && i >= 0))
            {
                vec.push_back((i * 10) + j);
                i = i - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x;
        j = y+1;
        if(j<=7) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        j = y-1;
        if(j>=0) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        vec.push_back(legal_move);
        return vec;
    }
    if(selected_peice==4)
    {
        int i=x+1;
        int j=y+1;
        if(i<=7 && j<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x+1;
        j=y-1;
        if(i<=7 && j>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y+1;
        if(j<=7 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >=0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y-1;
        if(j>=0 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
    }
    if(selected_peice==3)
    {
        int i=x;
        int j=y;
        //lower right quad
        if(((i+1)<=7 && (i+1)>=0)&& j+2<=7 && j+2>=0 && board[i+1][j+2]<=0 )
        {

            vec.push_back(((i+1) * 10) + j+2);
            legal_move = legal_move + 1;
        }
        if(((i+2)<=7 && (i+2)>=0)&& j+1<=7 && j+1>=0 && board[i+2][j+1]<=0  )
        {
            vec.push_back(((i+2) * 10) + j+1);
            legal_move = legal_move + 1;
        }
        // lower left quad
        if(((i+1)<=7 && (i+1)>=0)&& j-2<=7 && j-2>=0 && board[i+1][j-2]<=0 )
        {

            vec.push_back(((i+1) * 10) + j-2);
            legal_move = legal_move + 1;
        }
        if(((i+2)<=7 && (i+2)>=0)&& j-1<=7 && j-1>=0 && board[i+2][j-1]<=0  )
        {
            vec.push_back(((i+2) * 10) + j-1);
            legal_move = legal_move + 1;
        }
        //upper left quad
        if(((i-1)<=7 && (i-1)>=0)&& j-2<=7 && j-2>=0 && board[i-1][j-2]<=0 )
        {

            vec.push_back(((i-1) * 10) + j-2);
            legal_move = legal_move + 1;
        }
        if(((i-2)<=7 && (i-2)>=0)&& j-1<=7 && j-1>=0 && board[i-2][j-1]<=0  )
        {
            vec.push_back(((i-2) * 10) + j-1);
            legal_move = legal_move + 1;
        }
        //upper right quad
        if(((i-1)<=7 && (i-1)>=0)&& j+2<=7 && j+2>=0 && board[i-1][j+2]<=0 )
        {

            vec.push_back(((i-1) * 10) + j+2);
            legal_move = legal_move + 1;
        }
        if(((i-2)<=7 && (i-2)>=0)&& j+1<=7 && j+1>=0 && board[i-2][j+1]<=0  )
        {
            vec.push_back(((i-2) * 10) + j+1);
            legal_move = legal_move + 1;
        }
    }
    if(selected_peice==9)
    {
        int i=x+1;
        int j=y;
        if(i<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x-1;

        if(i>=0) {
            while (board[i][j] == 0 && (i < 8 && i >= 0))
            {
                vec.push_back((i * 10) + j);
                i = i - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x;
        j = y+1;
        if(j<=7) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        j = y-1;
        if(j>=0) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x+1;
        j=y+1;
        if(i<=7 && j<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x+1;
        j=y-1;
        if(i<=7 && j>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y+1;
        if(j<=7 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >=0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y-1;
        if(j>=0 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] < 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }

    }
    if(selected_peice==100)
    {
        for (int i=x-1;i<=x+1;i++)
        {
            for(int j=y-1;j<=y+1;j++)
            {
             if(i==x && j==y)
             {
                continue;
             }
             if(board[i][j] <= 0 && i < 8 && i >= 0 && j<8 && j >=0)
             {
                vec.push_back((i * 10) + j);
                legal_move = legal_move + 1;
             }
            }
        }
        if(q_k_w==1 && castle==1 && board[7][1]==0 && board[7][2]==0 && board[7][3]==0)
        {
            vec.push_back(72);
            legal_move = legal_move + 1;
        }
        if(k_k_w==1 && castle==1 && board[7][5]==0 && board[7][6]==0 )
        {
            vec.push_back(76);
            legal_move = legal_move + 1;
        }
    }
    if(selected_peice==-1)
    {
        if(board[x+1][y]==0 && board[x+2][y]==0 && x==1)
        {
            legal_move = legal_move +2;
            vec.push_back((x+1)*10 + y);
            vec.push_back((x+2)*10 + y);
        }
        if (board[x+1][y]==0 && x!=1 )
        {
            legal_move = legal_move +1;
            vec.push_back((x+1)*10 + y);
        }
        if(y!=0 && y!=7)
        {
            if(board[x+1][y+1]>0 && board[x+1][y-1]>0 )
            {
                legal_move = legal_move +2;
                vec.push_back((x+1)*10 + (y+1));
                vec.push_back((x+1)*10 + (y-1));
            }
            if((board[x+1][y+1]>0 && (board[x+1][y-1]==0 || board[x+1][y-1]<0 )) || ((board[x+1][y+1]==0 || board[x+1][y+1]<0) && board[x+1][y-1]>0))
            {
                legal_move = legal_move +1;
                if(board[x+1][y+1]>0 && (board[x+1][y-1]==0 || board[x+1][y-1]<0 ))
                {
                    vec.push_back((x+1)*10 + (y+1));
                }
                if(board[x+1][y-1]>0 && (board[x+1][y+1]==0 || board[x+1][y+1]<0)){
                    vec.push_back((x+1)*10 + (y-1));
                }
            }
        }
        if(y==0){
            if(board[x-1][y+1]>0 )
            {
                legal_move = legal_move +1;
                vec.push_back((x-1)*10 + (y+1));
            }
        }
        if(y==7)
        {
            if(board[x-1][y-1]>0 )
            {
                legal_move = legal_move +1;
                vec.push_back((x-1)*10 + (y-1));
            }
        }

    }
    if(selected_peice==-5)
    {
        int i=x+1;
        int j=y;
        if(i<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x-1;

        if(i>=0) {
            while (board[i][j] == 0 && (i < 8 && i >= 0))
            {
                vec.push_back((i * 10) + j);
                i = i - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x;
        j = y+1;
        if(j<=7) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        j = y-1;
        if(j>=0) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        vec.push_back(legal_move);
        return vec;
    }
    if(selected_peice==-4)
    {
        int i=x+1;
        int j=y+1;
        if(i<=7 && j<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x+1;
        j=y-1;
        if(i<=7 && j>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y+1;
        if(j<=7 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >=0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y-1;
        if(j>=0 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
    }
    if(selected_peice==-3)
    {
        int i=x;
        int j=y;
        //lower right quad
        if(((i+1)<=7 && (i+1)>=0)&& j+2<=7 && j+2>=0 && board[i+1][j+2]>=0 )
        {

            vec.push_back(((i+1) * 10) + j+2);
            legal_move = legal_move + 1;
        }
        if(((i+2)<=7 && (i+2)>=0)&& j+1<=7 && j+1>=0 && board[i+2][j+1]>=0  )
        {
            vec.push_back(((i+2) * 10) + j+1);
            legal_move = legal_move + 1;
        }
        // lower left quad
        if(((i+1)<=7 && (i+1)>=0)&& j-2<=7 && j-2>=0 && board[i+1][j-2]>=0 )
        {

            vec.push_back(((i+1) * 10) + j-2);
            legal_move = legal_move + 1;
        }
        if(((i+2)<=7 && (i+2)>=0)&& j-1<=7 && j-1>=0 && board[i+2][j-1]>=0  )
        {
            vec.push_back(((i+2) * 10) + j-1);
            legal_move = legal_move + 1;
        }
        //upper left quad
        if(((i-1)<=7 && (i-1)>=0)&& j-2<=7 && j-2>=0 && board[i-1][j-2]>=0 )
        {

            vec.push_back(((i-1) * 10) + j-2);
            legal_move = legal_move + 1;
        }
        if(((i-2)<=7 && (i-2)>=0)&& j-1<=7 && j-1>=0 && board[i-2][j-1]>=0  )
        {
            vec.push_back(((i-2) * 10) + j-1);
            legal_move = legal_move + 1;
        }
        //upper right quad
        if(((i-1)<=7 && (i-1)>=0)&& j+2<=7 && j+2>=0 && board[i-1][j+2]>=0 )
        {

            vec.push_back(((i-1) * 10) + j+2);
            legal_move = legal_move + 1;
        }
        if(((i-2)<=7 && (i-2)>=0)&& j+1<=7 && j+1>=0 && board[i-2][j+1]>=0  )
        {
            vec.push_back(((i-2) * 10) + j+1);
            legal_move = legal_move + 1;
        }
    }
    if(selected_peice==-9)
    {
        int i=x+1;
        int j=y;
        if(i<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x-1;

        if(i>=0) {
            while (board[i][j] == 0 && (i < 8 && i >= 0))
            {
                vec.push_back((i * 10) + j);
                i = i - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i = x;
        j = y+1;
        if(j<=7) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        j = y-1;
        if(j>=0) {
            while (board[i][j] == 0 && j < 8 && j >= 0) {
                vec.push_back((i * 10) + j);
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (j < 8 && j >= 0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x+1;
        j=y+1;
        if(i<=7 && j<=7) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x+1;
        j=y-1;
        if(i<=7 && j>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i + 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y+1;
        if(j<=7 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >=0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j + 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        i=x-1;
        j=y-1;
        if(j>=0 && i>=0) {
            while (board[i][j] == 0 && i < 8 && i >= 0 && j<8 && j >=0) {
                vec.push_back((i * 10) + j);
                i = i - 1;
                j = j - 1;
                legal_move = legal_move + 1;
            }
            if (i < 8 && i >= 0 && j<8 && j >=0) {
                if (board[i][j] > 0) {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }

    }
    if(selected_peice==-100)
    {

        for (int i=x-1;i<=x+1;i++)
        {
            for(int j=y-1;j<=y+1;j++)
            {
                if(i==x && j==y)
                {
                    continue;
                }
                if(board[i][j] >= 0 && i < 8 && i >= 0 && j<8 && j >=0)
                {
                    vec.push_back((i * 10) + j);
                    legal_move = legal_move + 1;
                }
            }
        }
        if(q_k_b==1 && castle_b==1 && board[0][1]==0 && board[0][2]==0 && board[0][3]==0)
        {
            vec.push_back(02);
            legal_move = legal_move + 1;
        }
        if(k_k_b==1 && castle_b==1 && board[0][5]==0 && board[0][6]==0 )
        {
            vec.push_back(06);
            legal_move = legal_move + 1;
        }
    }

    vec.push_back(legal_move);
    return vec;
}

void push(int x)
{
    int i =-1;
    int j = -1;
    int x_1 = -1;
    int y_1 = -1;
    int x_2 = -1;
    int y_2 = -1;

    if(x/1000 == 9)
    {

        x_1 = 0;
        i=x/100;
        j = x % 100;
        y_1 = i %10;
        x_2 = j / 10;
        y_2 = j % 10;

    }
    else {
        i = x / 100;
        j = x % 100;
        x_1 = i / 10;
        y_1 = i % 10;
        x_2 = j / 10;
        y_2 = j % 10;
    }
    if(board[x_1][y_1]==0)
    {
        std::cout<<"illegal move: no piece fond \n";


    }


    else{

        std::vector<int> vec = legal_move_per_piece(x_1,y_1);

        int k_1 =-1;
        int k_2 =-1;
        for (int k:vec)
        {
            if(k/10==0)
            {
                k_1=0;
                k_2 = k%10;
            }
            if(k/10!=0) {
                k_1 = k / 10;
                k_2 = k % 10;
            }
            if(k_1==x_2 && k_2==y_2)
            {
                if(board[x_1][y_1]==100 && (y_2==6 || y_2==2)){
                    if(y_2==6)
                    {
                        board[x_2][y_2] =  100;
                        board[x_1][y_1] = 0;
                        board[7][5] = 5;
                        board[7][7]=0;
                        castle=0;
                        last_move.push_back(76);
                        last_p.push_back(0);
                        if(player==1)
                        {
                            player=0;
                            return;
                        }
                        if(player==0)
                        {
                            player=1;
                            return;
                        }
                    }
                    if(y_2==2)
                    {
                        board[7][2] =  100;
                        board[x_1][y_1] = 0;
                        board[7][3] = 5;
                        board[7][0]=0;
                        castle=0;
                        last_move.push_back(72);
                        last_p.push_back(0);
                        if(player==1)
                        {
                            player=0;
                            return;
                        }
                        if(player==0)
                        {
                            player=1;
                            return;
                        }
                    }
                }
                if(board[x_1][y_1]==-100 && (y_2==6 || y_2==2)){
                    if(y_2==6)
                    {
                        board[x_2][y_2] =  -100;
                        board[x_1][y_1] = 0;
                        board[0][5] = -5;
                        board[0][7]=0;
                        castle_b=0;
                        last_move.push_back(6);
                        last_p.push_back(0);
                        if(player==1)
                        {
                            player=0;
                            return;
                        }
                        if(player==0)
                        {
                            player=1;
                            return;
                        }
                    }
                    if(y_2==2)
                    {
                        board[x_2][y_2] =  -100;
                        board[x_1][y_1] = 0;
                        board[0][3] = -5;
                        board[0][0]=0;
                        castle_b=0;
                        last_move.push_back(2);
                        last_p.push_back(0);
                        if(player==1)
                        {
                            player=0;
                            return;
                        }
                        if(player==0)
                        {
                            player=1;
                            return;
                        }
                    }
                }
                else {
                    if (board[x_1][y_1] == 5 && x_1 == 7 && y_1 == 0) {
                        q_k_w = 0;
                    }
                    if (board[x_1][y_1] == 5 && x_1 == 7 && y_1 == 7) {
                        k_k_w = 0;
                    }
                    if (board[x_1][y_1] == 100) {
                        castle = 0;
                    }
                    if (board[x_1][y_1] == -5 && x_1 == 0 && y_1 == 0) {
                        q_k_b = 0;
                    }
                    if (board[x_1][y_1] == -5 && x_1 == 0 && y_1 == 7) {
                        k_k_b = 0;
                    }
                    if (board[x_1][y_1] == -100) {
                        castle_b = 0;
                    }
                    last_p.push_back(board[x_2][y_2]);
                    board[x_2][y_2] = board[x_1][y_1];
                    board[x_1][y_1] = 0;
                    if(x_2==0)
                    {
                       x_2=9;
                    }
                    last_move.push_back(x_2*1000 + y_2*100 + x_1*10 + y_1);
                    if(player==1)
                    {
                        player=0;
                        return;
                    }
                    if(player==0)
                    {
                        player=1;
                        return;
                    }
                }

                return;
            }

        }
        std::cout<<"illegal move  ";
    }
}
void pop()
{
    int last = last_move.back();  // Get the last element of last_move
    last_move.pop_back();         // Remove the last element from last_move

    int last_p_p = last_p.back(); // Get the last element of last_p
    last_p.pop_back();            // Remove the last element from last_p

    if(last == 76)
    {
        board[7][5] = 0;
        board[7][7]=5;
        board[7][6]=0;
        board[7][4]=100;
        castle=1;
        if(player==1)
        {
            player=0;
            return;
        }
        if(player==0)
        {
            player=1;
            return;
        }
    }
    if(last == 72)
    {

        board[7][3] = 0;
        board[7][0] = 5;
        board[7][2] = 0;
        board[7][4] = 100;
        castle=1;
        if(player==1)
        {
            player=0;
            return;
        }
        if(player==0)
        {
            player=1;
            return;
        }
    }
    if(last == 2)
    {

        board[0][3] = 0;
        board[0][0] = -5;
        board[0][2] = 0;
        board[0][4] = -100;
        castle_b=1;
        if(player==1)
        {
            player=0;
            return;
        }
        if(player==0)
        {
            player=1;
            return;
        }
    }
    if(last == 6)
    {
        board[0][5] = 0;
        board[0][7] = -5;
        board[0][6] = 0;
        board[0][4] =-100;
        castle_b=1;
        if(player==1)
        {
            player=0;
            return;
        }
        if(player==0)
        {
            player=1;
            return;
        }
    }
    else
    {
        int x_1 = last/1000;
        if(x_1==9)
        {
            x_1=0;
        }
        int y_1 = (last/100)%10;
        int x_2 = (last/10)%10;
        int y_2 = last%10;
        board[x_2][y_2] = board[x_1][y_1];
        board[x_1][y_1] = last_p_p;
        if(player==1)
        {
            player=0;
            return;
        }
        if(player==0)
        {
            player=1;
            return;
        }
    }
}


void setup()
{
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<8;j++)
        {

            if(i==0)
            {
                if(j==0 || j==7){
                    board[i][j] = -5;
                }
                if(j==1 || j==6){
                    board[i][j] = -3;
                }
                if(j==2 || j==5){
                    board[i][j] = -4;
                }
                if(j==3){
                    board[i][j] = -9;
                }
                if(j==4){
                    board[i][j] = -100;
                }
            }
            else {
                if (i == 1 ) {
                    board[i][j] = -1;
                }
                if (i==6){
                    board[i][j] = 1;
                }

            }
            if(i==7)
            {
                if(j==0 || j==7){
                    board[i][j] = 5;
                }
                if(j==1 || j==6){
                    board[i][j] = 3;
                }
                if(j==2 || j==5){
                    board[i][j] = 4;
                }
                if(j==3){
                    board[i][j] = 9;
                }
                if(j==4){
                    board[i][j] = 100;
                }
            }



        }
    }
}
std::vector<int> edited_legal_move(int x,int y)
{
    std::vector<int> final;
    std::vector<int> vec = legal_move_per_piece(x,y);
    for (int i:vec)
    {
        if(x!=0)
        {
            final.push_back((x*10+y)*100 + i);
        }
        if(x==0)
        {
            final.push_back((9*10+y)*100 + i);
        }
    }
    final.pop_back();
    return final;
}
std::vector<int> all_legal_move(int color)//1 for white 0 for black
{
    std::vector<int> final;
    std::vector<int> temp;
    if(color==1)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(board[i][j]>0)
                {
                    temp = edited_legal_move(i,j);
                    for (int k : temp) {
                        final.push_back(k);
                    }
                }
            }
        }
    }
    if(color==0)
    {

        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(board[i][j]<0)
                {
                    temp = edited_legal_move(i,j);
                    for (int k : temp) {
                        final.push_back(k);
                    }
                }
            }
        }
    }
    return final;
}

int eval()
{
    int e;
    int pawn_count = 0;
    int knight_count = 0;
    int bishop_count =0;
    int rook_count = 0;
    int queen_count = 0;
    int king_count = 0;
    int pawn_count_b = 0;
    int knight_count_b = 0;
    int bishop_count_b =0;
    int rook_count_b = 0;
    int queen_count_b = 0;
    int king_count_b = 0;
    for (int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(board[i][j]==5)
                {
                    rook_count++;
                }
                if(board[i][j]==3)
                {
                    knight_count++;
                }
                if(board[i][j]==4)
                {
                    bishop_count++;
                }
                if(board[i][j]==9)
                {
                    queen_count++;
                }
                if(board[i][j]==1)
                {
                    pawn_count++;
                }
                if(board[i][j]==100)
                {
                    king_count++;
                }
                if(board[i][j]==-5)
                {
                    rook_count_b++;
                }
                if(board[i][j]==-3)
                {
                    knight_count_b++;
                }
                if(board[i][j]==-4)
                {
                    bishop_count_b++;
                }
                if(board[i][j]==-9)
                {
                    queen_count_b++;
                }
                if(board[i][j]==-1)
                {
                    pawn_count_b++;
                }
                if(board[i][j]==-100)
                {
                    king_count_b++;
                }
            }
        }
        e = e +  pawn_count * 100;
        e = e + knight_count * 320;
        e = e + bishop_count * 330;
        e = e +  rook_count * 500;
        e = e + queen_count * 900;
        e = e + king_count * 20000;
        e = e -  pawn_count_b * 100;
        e = e - knight_count_b * 320;
        e = e - bishop_count_b * 330;
        e = e -  rook_count_b * 500;
        e = e - queen_count_b * 900;
        e = e - king_count_b * 20000;

        int f=0;
        for (int i=0;i<8;i++)
        {
            for (int j = 0; j < 8; j++)
            {

                if(board[i][j]==5)
                {
                    f = f + rook_table[i][j];
                }
                if(board[i][j]==3)
                {
                    f = f + knight_table[i][j];
                }
                if(board[i][j]==4)
                {
                    f = f + bishop_table[i][j];
                }
                if(board[i][j]==9)
                {
                    f = f + queen_table[i][j];
                }
                if(board[i][j]==1)
                {
                    f = f + pawn_table[i][j];
                }
                if(board[i][j]==100)
                {
                    f = f + king_table[i][j];
                }
                if(board[i][j]==-5)
                {
                    f = f - rook_table[7-i][j];
                }
                if(board[i][j]==-3)
                {
                    f = f - knight_table[7-i][j];
                }
                if(board[i][j]==-4)
                {
                    f = f - bishop_table[7-i][j];
                }
                if(board[i][j]==-9)
                {

                    f = f - queen_table[7-i][j];
                }
                if(board[i][j]==-1)
                {
                    f = f - pawn_table[7-i][j];
                }
                if(board[i][j]==-100)
                {
                    f = f - king_table[7-i][j];
                }
            }
        }


    return e+f ;
}
int check_mate()
{
    if(player==1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == 100) {
                    std::vector<int> l = legal_move_per_piece(i, j);
                    if (l[0] == 0) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
        if(player==0)
        {
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(board[i][j]==-100)
                    {
                        std::vector<int> l = legal_move_per_piece(i,j);
                        if(l[0]==0)
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                }
            }

          }
}

void play_random()
{
    std::vector<int> m;
    m = all_legal_move(player);
    push(m[5]);
    if(player==1)
    {
        player=0;
        return;
    }
    if(player==0)
    {
        player=1;
        return;
    }

}

int engine(int depth, int alpha, int beta, int color)
{

    if (depth == 0) {

        return eval();
    }
    if (color == 1) {


        int max_eval = -2000000;
        std::vector<int> m = all_legal_move(1);
        for (int i:m) {

            push(i);
            display();
            int evaluation = engine(depth - 1, alpha, beta,0);

            if (evaluation > max_eval)
            {
                max_eval = evaluation;
                best_move = i;
            }

            pop();

            if (max_eval >= beta) {
                break;
            }
            if(alpha>max_eval)
            {
                alpha=alpha;
            }
            if(alpha<max_eval)
            {
                alpha=max_eval;
            }

        }

        return max_eval;
    }
    if(color==0)
    {

        int min_eval = 2000000;
        std::vector<int> n = all_legal_move(0);
        for (int i:n) {

            push(i);

            int evaluation = engine(depth - 1, alpha, beta,1);

            pop();
            if (evaluation < min_eval) {
                min_eval = evaluation;
                best_move = i;
            }
            pop();


            if (min_eval <= beta) {
                break;
            }
            if(alpha<min_eval)
            {
                alpha=alpha;
            }
            if(alpha>min_eval)
            {
                alpha=min_eval;
            }

        }

        return min_eval;
    }
}
void best_move_1(int color)
{
    int c=0;
    int c_1=0;
    int max_eval=1000000000;
    if(color==1)
    {
        int c=1;
        int c_1 = 0;
        int max_eval=-1000000000;
    }
    else
    {
        int c=0;
        int c_1 = 1;
        int max_eval=1000000000;
    }
    int best_move1 =0;
    std::vector<int> m = all_legal_move(c);
    for (int i: m) {
        push(i);
        std::vector<int> k = all_legal_move(c_1);
        for (int j: k) {
            push(j);
            std::vector<int> q = all_legal_move(c);
            for (int l: q) {
                push(l);
                std::vector<int> o = all_legal_move(c_1);
                for (int p: o) {
                    push(p);
                    if (eval() > max_eval) {
                        max_eval = eval();
                        best_move1 = i;
                    }
                    pop();
                }
                pop();
            }
            pop();
        }
        pop();
    }
    push(best_move1);
    display();
}

int main()
{
    setup();
    display();

//    push(1737);
//    display();
//    push(9717);
//    display();
//    push(7655);
//    display();
//    pop();
//    display();
//    pop();
//    display();
//    pop();
//    display();


//    int f = eval();
//
//    std::cout<<f;
//    play_random();
//    display();
//    f = eval();
//    std::cout<<"\n"<<f<<"\n";
//    display();
//    std::cout<<"\n"<<player;
//    engine(10, -1000000, 1000000,player);
//    std::cout<<"\n"<<best_move;
////    std::cout<<"\n"<<player;
////    std::cout<<"\n";
////    push(9122);
//    display();
//


int max_eval=-1000000000;
int best_move1=0;
std::cout<<"checking best move \n";

display();
std::cout<<"\n"<<best_move1<<"\n";
push(best_move1);
display();
//max_eval=1000000000;
//best_move1=0;
//    std::vector<int> h = all_legal_move(0);
//    for(int i:h)
//    {
//        push(i);
//        std::vector<int> k = all_legal_move(1);
//        for(int j:k)
//        {
//            push(j);
//            std::vector<int> q = all_legal_move(0);
//            for(int l:q) {
//                push(l);
//                if (eval() < max_eval) {
//                    max_eval = eval();
//                    best_move1 = i;
//                }
//                pop();
//            }
//
//            pop();
//        }
//        pop();
//    }
//
//    display();
//    std::cout<<"\n"<<best_move1<<"\n";
//    push(best_move1);
//    display();
////    std::cout<<"\n"<<y;
    best_move_1(0);
}