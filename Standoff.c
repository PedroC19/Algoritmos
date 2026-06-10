#include <stdio.h>
#include <stdlib.h>

#define VAZIO_ 0
#define BIGODE_ 1
#define CAPETA_ 2

int n_;
int b_;
int c_;

int tabuleiro_[20][20];

long long solucoes_ = 0;

int dx_[8] = {-1,-1,-1,0,0,1,1,1};
int dy_[8] = {-1,0,1,-1,1,-1,0,1};

int dentro_(int x_, int y_)
{
    return x_ >= 0 && x_ < n_ && y_ >= 0 && y_ < n_;
}

int configuracao_valida_()
{
    for(int i_ = 0; i_ < n_; i_++)
    {
        for(int j_ = 0; j_ < n_; j_++)
        {
            if(tabuleiro_[i_][j_] == VAZIO_)
                continue;

            int tipo_ = tabuleiro_[i_][j_];
            int aliados_ = 0;
            int inimigos_ = 0;

            for(int d_ = 0; d_ < 8; d_++)
            {
                int x_ = i_ + dx_[d_];
                int y_ = j_ + dy_[d_];

                while(dentro_(x_, y_))
                {
                    if(tabuleiro_[x_][y_] != VAZIO_)
                    {
                        if(tabuleiro_[x_][y_] == tipo_)
                            aliados_++;
                        else
                            inimigos_++;

                        break; /* primeira peça bloqueia a visão */
                    }

                    x_ += dx_[d_];
                    y_ += dy_[d_];
                }
            }

            if(aliados_ > 0)
                return 0;

            if(inimigos_ < 2)
                return 0;
        }
    }

    return 1;
}

void backtracking_(int pos_, int b_restantes_, int c_restantes_)
{
    int casas_restantes_ = n_ * n_ - pos_;

    if(b_restantes_ + c_restantes_ > casas_restantes_)
        return;

    if(pos_ == n_ * n_)
    {
        if(b_restantes_ == 0 && c_restantes_ == 0)
        {
            if(configuracao_valida_())
                solucoes_++;
        }
        return;
    }

    int linha_ = pos_ / n_;
    int coluna_ = pos_ % n_;

    /* deixa vazio */
    tabuleiro_[linha_][coluna_] = VAZIO_;
    backtracking_(pos_ + 1, b_restantes_, c_restantes_);

    /* coloca Bigodudo */
    if(b_restantes_ > 0)
    {
        tabuleiro_[linha_][coluna_] = BIGODE_;
        backtracking_(pos_ + 1, b_restantes_ - 1, c_restantes_);
    }

    /* coloca Capeta */
    if(c_restantes_ > 0)
    {
        tabuleiro_[linha_][coluna_] = CAPETA_;
        backtracking_(pos_ + 1, b_restantes_, c_restantes_ - 1);
    }

    tabuleiro_[linha_][coluna_] = VAZIO_;
}

int main(int argc_, char *argv_[])
{
    if(argc_ != 4)
    {
        printf("Uso: %s n b c\n", argv_[0]);
        return 1;
    }

    n_ = atoi(argv_[1]);
    b_ = atoi(argv_[2]);
    c_ = atoi(argv_[3]);

    backtracking_(0, b_, c_);

    printf("%lld\n", solucoes_);

    return 0;
}