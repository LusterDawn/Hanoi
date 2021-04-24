#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//声明栈数据结构
struct Stack
{
	int* top;
	int* bottom;
	int data[64];
};
struct Stack A = { &A.data[1],&A.data[0],0 };//定义三个栈（由于盘子只能在上面出入，不能在下方出入）
struct Stack B = { &B.data[1],&B.data[0],0 };
struct Stack C = { &C.data[1],&C.data[0],0 };

//定义与输入相关的变量
char Skip=NULL;
int input = 0, safeinput = 0, tempinput = 0, TargetHeight = 0, k = 0,state=1;
long count = 0;

//主函数
int main()
{
	void hanoi(int num);																		 //木块归位函数声明
	while (1)//输入模块
	{
		safeinput = 0;
		while (safeinput != 1)																 //输入检测（防止字符输入）
		{
			printf("    汉诺塔外挂\n请输入汉诺塔的阶数\n");
			printf("  按ESC退出本程序\n");
			safeinput = scanf_s("%d", &input);
			if (_getch() == 27) { return 0; }
			if (safeinput != 1) { while (getchar() != '\n'); }//吃字符记得添加这个条件，否则会导致第一次输入要重复多一次
		}
		//预处理无需递归的数据和初始化递归的起点
		if (input < 1 || input>63)
		{
			printf("请输入大于1,小于63的正整数\n    请重新输入\n");      //防止错误数字输入
			continue;
		}
		if (input == 1)
		{
			printf("A->C\n");
			continue;
		}
		//初始化各个指针和数据
		for (k = 0; k < 64; k++)
		{
			A.data[k] = 0;
			B.data[k] = 0;
			C.data[k] = 0;
		}
		A.top = &A.data[1];
		B.top = &B.data[1];
		C.top = &C.data[1];
		A.bottom = &A.data[0];
		B.bottom = &B.data[0];
		C.bottom = &C.data[0];

		tempinput = input;
		TargetHeight = 0;
		Skip = NULL;
		count = 0;
		
		for (k = 1; k <= tempinput; k++)
		{
			A.data[k] = input--;
			A.top++;
		}
		//开始进入汉诺塔的函数递归


		hanoi(tempinput);
		printf("一共需要移动的总步骤数\n");
		printf("%ld\n", count-1);
	}
}

//汉诺塔函数
void hanoi(int number)
{
	//设定本次嵌套需要达到的目标高度
	TargetHeight++;
	//通过不断拆解和重组最初时在最顶上的两块木块1.2来让比木块1.2大的木块有空间进行重新组合（开辟空间给大木块）
	while (number % 2 == 0)//阶数为偶数的情况
	{
		//判断函数终止，退出递归的条件（C柱上两个指针变量的差值==输入高度的大小+1）
		if ((C.top - C.bottom) == (tempinput + 1)) { break; }
		
		//非1/2元素归位操作（归位的原则：观察两个没有出现1/2的柱子，出现空柱子就补上，没有空位就比较顶木块大小，小的木块去大的木块上）
		switch (Skip)
		{
		case'A':
			if (     (  (*(C.top - 1) < *(B.top - 1)) && (*(C.top - 1)!=0))    ||   (*(B.top - 1) == 0)	    )
			{
				*B.top = *(C.top - 1);
				C.top--;
				*C.top = 0;
				B.top++;
				if (state == 1)
				{
					printf("C->B\n\n");
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        *       <--------\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			else
			{
				*C.top = *(B.top - 1);
				B.top--;
				*B.top = 0;
				C.top++;
				if (state == 1)
				{
					printf("B->C\n\n");
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        *       -------->\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
				
			}
			break;

		case'B':
			if (      ( (*(A.top - 1) < *(C.top - 1)) && (*(A.top-1)!=0) )   ||   (*(C.top - 1) == 0)     )
			{
				*C.top = *(A.top - 1);
				A.top--;
				*A.top = 0;
				C.top++;
				if(state == 1)
				{
					printf("A->C\n\n");
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        ---------------->\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}

			}
			else
			{
				*A.top = *(C.top - 1);
				C.top--;
				*C.top = 0;
				A.top++;
				if(state == 1)
				{
					printf("C->A\n\n");
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("       <----------------\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}

			}
			break;

		case'C':
			if (		( (*(A.top - 1) < *(B.top - 1))  &&  (*(A.top-1)!=0))   ||   (*(B.top - 1) == 0)  	)
			{
				*B.top = *(A.top - 1);
				A.top--;
				*A.top = 0;
				B.top++;
				if(state == 1)
				{
					printf("A->B\n");
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        -------->       *\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}

			}
			else
			{
				*A.top = *(B.top - 1);
				B.top--;
				*B.top = 0;
				A.top++;
				printf("B->A\n");
				if(state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        <--------       *\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}

			}
			break;
		}

		count++;

		//逐个检查1.2木块共存的柱子，开始2/1操作（这是一个我通过暴力枚举发现的规律，我们只需要关注1/2木块的位置）
		if (*(A.top-1) == 1)
		{
			//木块1：A->B
			*B.top = *(A.top - 1);
			A.top--;
			*A.top = 0;
			B.top++;
			//木块2：A->C
			*C.top = *(A.top - 1);
			A.top--;
			*A.top = 0;
			C.top++;
			//木块1：B->C
			*C.top = *(B.top - 1);
			B.top--;
			*B.top = 0;
			C.top++;
			//标记21木块共存的柱子，归位操作的时候不再需要考虑其移动
			Skip = 'C';
			printf("A->B\n");
			printf("A->C\n");
			printf("B->C\n");
			if (state == 1)
			{
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        -------->       *\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        ---------------->\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        *       -------->\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
			}
		}
		else if (*(B.top - 1) == 1)
		{
			//木块1：B->C
			*C.top = *(B.top - 1);
			B.top--;
			*B.top = 0;
			C.top++;
			//木块2：B->A
			*A.top = *(B.top - 1);
			B.top--;
			*B.top = 0;
			A.top++;
			//木块1：C->A
			*A.top = *(C.top - 1);
			C.top--;
			*C.top = 0;
			A.top++;
			//标记21木块共存的柱子，归位操作的时候不再需要考虑其移动
			Skip = 'A';
			printf("B->C\n");
			printf("B->A\n");
			printf("C->A\n");
			if (state == 1)
			{
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        *       -------->\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        <--------       *\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("       <----------------\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
			}
		}
		else if(*(C.top - 1) == 1)
		{
			//木块1：C->A
			*A.top = *(C.top - 1);
			C.top--;
			*C.top = 0;
			A.top++;
			//木块2：C->B
			*B.top = *(C.top - 1);
			C.top--;
			*C.top = 0;
			B.top++;
			//木块1：A->B
			*B.top = *(A.top - 1);
			A.top--;
			*A.top = 0;
			B.top++;
			//标记21木块共存的柱子，归位操作的时候不再需要考虑其移动
			Skip = 'B';
			printf("C->A\n");
			printf("C->B\n");
			printf("A->B\n");
			if (state == 1)
			{
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("       <----------------\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        *       <--------\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        -------->       *\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
			}
		}

		count += 3;

		//检测上一次2/1操作后，是否产生了本次递归目标高度的塔，如果是，就进入下一次递归
		if ( (*(A.bottom + 1) -*(A.top - 1)  == TargetHeight)  ||  ( *(B.bottom + 1)- *(B.top - 1)  == TargetHeight) || (*(C.bottom + 1) -*(C.top - 1)   == TargetHeight))
		{
			hanoi(number);
		}
	}
	/*---------------------------------------------------------------------------------*/
	while (number % 2 != 0)//阶数为奇数的情况
	{
		//判断函数终止，退出递归的条件
		if ((C.top - C.bottom) == (tempinput + 1)) {break; }

		//非1/2元素归位操作（归位的原则：观察两个没有出现1/2的柱子，出现空柱子就补上，没有空位就比较顶木块大小，小的木块去大的木块上）
		switch (Skip)
		{
		case'A':
			if (((*(C.top - 1) < *(B.top - 1)) && (*(C.top - 1) != 0)) || (*(B.top - 1) == 0))
			{
				*B.top = *(C.top - 1);
				C.top--;
				*C.top = 0;
				B.top++;
				printf("C->B\n\n");
				if (state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        *       <--------\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			else
			{
				*C.top = *(B.top - 1);
				B.top--;
				*B.top = 0;
				C.top++;
				printf("B->C\n\n");
				if (state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        *       -------->\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			break;

		case'B':
			if (((*(A.top - 1) < *(C.top - 1)) && (*(A.top - 1) != 0)) || (*(C.top - 1) == 0))
			{
				*C.top = *(A.top - 1);
				A.top--;
				*A.top = 0;
				C.top++;
				printf("A->C\n\n");
				if (state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        ---------------->\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			else
			{
				*A.top = *(C.top - 1);
				C.top--;
				*C.top = 0;
				A.top++;
				printf("C->A\n\n");
				if (state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("       <----------------\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			break;

		case'C':
			if (((*(A.top - 1) < *(B.top - 1)) && (*(A.top - 1) != 0)) || (*(B.top - 1) == 0))
			{
				*B.top = *(A.top - 1);
				A.top--;
				*A.top = 0;
				B.top++;
				printf("A->B\n");
				if (state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        -------->       *\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			else
			{
				*A.top = *(B.top - 1);
				B.top--;
				*B.top = 0;
				A.top++;
				printf("B->A\n");
				if (state == 1)
				{
					printf("        *       *       *\n");
					printf("        *       *       *\n");
					printf("        <--------       *\n");
					printf("        *       *       *\n");
					printf("        A       B       C\n");
					printf("********************************\n\n\n");
				}
			}
			break;
		default:
				break;
		}

		count++;

		//逐个检查1.2木块共存的柱子，开始2/1操作
		if (*(A.top - 1) == 1)
		{
			//木块1：A->C
			*C.top = *(A.top - 1);
			A.top--;
			*A.top = 0;
			C.top++;
			//木块2：A->B
			*B.top = *(A.top - 1);
			A.top--;
			*A.top = 0;
			B.top++;
			//木块1：C->B
			*B.top = *(C.top - 1);
			C.top--;
			*C.top = 0;
			B.top++;
			//标记21木块共存的柱子，归位操作的时候不再需要考虑其移动
			Skip = 'B';
			printf("A->C\n");
			printf("A->B\n");
			printf("C->B\n");
			if (state == 1)
			{
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        ---------------->\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        -------->       *\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        *       <--------\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
			}
		}
		else if (*(B.top - 1) == 1)
		{
			//木块1：B->A
			*A.top = *(B.top - 1);
			B.top--;
			*B.top = 0;
			A.top++;
			//木块2：B->C
			*C.top = *(B.top - 1);
			B.top--;
			*B.top = 0;
			C.top++;
			//木块1：A->C
			*C.top = *(A.top - 1);
			A.top--;
			*A.top = 0;
			C.top++;
			//标记21木块共存的柱子，归位操作的时候不再需要考虑其移动
			Skip = 'C';
			printf("B->A\n");
			printf("B->C\n");
			printf("A->C\n");
			if (state == 1)
			{
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        <--------       *\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        *       -------->\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        ---------------->\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
			}
		}
		else if (*(C.top - 1) == 1)
		{
			//木块1：C->B
			*B.top = *(C.top - 1);
			C.top--;
			*C.top = 0;
			B.top++;
			//木块2：C->A
			*A.top = *(C.top - 1);
			C.top--;
			*C.top = 0;
			A.top++;
			//木块1：B->A
			*A.top = *(B.top - 1);
			B.top--;
			*B.top = 0;
			A.top++;
			//标记21木块共存的柱子，归位操作的时候不再需要考虑其移动
			Skip = 'A';
			printf("C->B\n");
			printf("C->A\n");
			printf("B->A\n");
			if (state == 1)
			{
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        *       <--------\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("       <----------------\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
				printf("        *       *       *\n");
				printf("        *       *       *\n");
				printf("        <--------       *\n");
				printf("        *       *       *\n");
				printf("        A       B       C\n");
				printf("********************************\n\n\n");
			}
		}

		count += 3;

		//检测上一次2/1操作后，是否产生了本次递归目标高度的塔，如果是，就进入下一次递归
		if ((*(A.bottom + 1) - *(A.top - 1) == TargetHeight) || (*(B.bottom + 1) - *(B.top - 1) == TargetHeight) || (*(C.bottom + 1) - *(C.top - 1) == TargetHeight))
		{
			hanoi(number);
		}
	}
	return;
}
