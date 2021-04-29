#include <cstdio>
#include <cstdlib>
#include <ctime>
class Field
{
    private:
        int empty_fields,hid_number[9][9],cor_number[9][9]={    1,2,3,4,5,6,7,8,9,
                                                                4,5,6,7,8,9,1,2,3,
                                                                7,8,9,1,2,3,4,5,6,
                                                                2,3,4,5,6,7,8,9,1,
                                                                5,6,7,8,9,1,2,3,4,
                                                                8,9,1,2,3,4,5,6,7,
                                                                3,4,5,6,7,8,9,1,2,
                                                                6,7,8,9,1,2,3,4,5,
                                                                9,1,2,3,4,5,6,7,8};
    public:
        Field()                                                                                 //конструктор
        {
            srand(time(0));
            for(int it=0;it<3;it++)
            {
                int it1=(rand()%3+0)+it*3,it2=0;
                do it2=(rand()%3+0)+it*3;
                while(it1==it2);
                for(int i1=0;i1<9;i1++)
                {
                    int temp=cor_number[i1][it1];
                    cor_number[i1][it1]=cor_number[i1][it2];
                    cor_number[i1][it2]=temp;
                }
            }
            for(int it=0;it<3;it++)
            {
                int it1=(rand()%3+0)+it*3,it2=0;
                do it2=(rand()%3+0)+it*3;
                while(it1==it2);
                for(int i1=0;i1<9;i1++)
                {
                    int temp=cor_number[it1][i1];
                    cor_number[it1][i1]=cor_number[it2][i1];
                    cor_number[it2][i1]=temp;
                }
            }
            int game_difficulty=rand()%4+2;
            printf("difficulty = %i\n",game_difficulty);
            empty_fields=game_difficulty*9;
            game_difficulty*=9;
            for(int i1=0;i1<9;i1++)for(int i2=0;i2<9;i2++)hid_number[i1][i2]=cor_number[i1][i2];
            for(;game_difficulty>0;--game_difficulty)
            {
                int i1=0,i2=0;
                do
                {
                    i1=rand()%9+0;
                    i2=rand()%9+0;
                }
                while(hid_number[i1][i2]==0);
                hid_number[i1][i2]=0;
            }
        }
        ~Field(){}                                                                              //деструктор
        void show_field()                                                                       //вывод полей
        {
            printf("'00' - Exit\n");
            printf("    ");
            for(int i1=0;i1<9;i1++)printf(" %i  ",1+i1);
            for(int i1=0;i1<9;i1++)
            {
                printf("\n   -");
                for(int i2=0;i2<9;i2++)printf("----");
                printf("\n %c |",i1+65);
                for(int i2=0;i2<9;i2++)if(hid_number[i1][i2]!=0)printf(" %i |",hid_number[i1][i2]);
                    else printf("   |");
                
            }
            printf("\n   -");
            for(int i1=0;i1<9;i1++)printf("----");
            printf("\n");
        }
        int check_empty_fields()                                                                //вывод количества пустых полей
        {
            return empty_fields;
        }
        bool check_field_status(char y,int x)                                                   //проверка заполнености поля
        {
            if((y>=65)&&(y<=73)&&(x>=1)&&(x<=9))
            {
                y-=65;
                x-=1;
                if(hid_number[y][x]==0)return true;
                else return false;
            }
            else return false;
        }
        void field_change(char y,int x,int field_value)                                         //заполнение полей
        {
            if((field_value>=1)&&(field_value<=9))
            {
                y-=65;
                x-=1;
                hid_number[y][x]=field_value;
            }
            else
            {
                printf("Value are not correct\n");
                system("pause");
            }
        }
        void check_result()                                                                     //результат
        {
            int mis=0;
            printf("'!' - Уour mistakes\n");
            printf("    ");
            for(int i1=0;i1<9;i1++)printf(" %i  ",1+i1);
            for(int i1=0;i1<9;i1++)
            {
                printf("\n   -");
                for(int i2=0;i2<9;i2++)printf("----");
                printf("\n %c |",i1+65);
                for(int i2=0;i2<9;i2++)if(hid_number[i1][i2]!=cor_number[i1][i2])
                {
                    mis++;
                    printf("!%i |",hid_number[i1][i2]);
                }
                else printf(" %i |",hid_number[i1][i2]);
                
            }
            printf("\n   -");
            for(int i1=0;i1<9;i1++)printf("----");
            printf("\nYou have %i mistakes\n",mis);
            if(mis==0)printf("Congratulations, you won!! =)\n");
            else printf("Try again. =(\n");
        }
};
int main()
{
    Field f_obj;
    f_obj.show_field();
    char y=NULL;
    int x=NULL;
    for(int i=f_obj.check_empty_fields();i>0;i--)
    {
        printf("Enter the coordinates of an empty field(A1): ");
        fflush(stdin);
        scanf("%c%i",&y,&x);
        if((y=='0')&&(x==0))i=0;
        else
        {
            if(f_obj.check_field_status(y,x))
            {
                printf("Enter new field value(1-9): ");
                int field_value=0;
                fflush(stdin);
                scanf("%i",&field_value);
                f_obj.field_change(y,x,field_value);
            }
            else 
            {
                printf("Coordinates are not correct or field not empty\n");
                system("pause");
                i++;
            }
            system("cls");
            f_obj.show_field();
        }
    }
    if((y!='0')&&(x!=0))
    {
        system("cls");
        f_obj.check_result();
        system("pause");
    }
}