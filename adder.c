#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
	int decimal;
	int bin[8];
	char binstr[9];
} dnb;

void getdnb(dnb *);
void adder(dnb * , dnb * , dnb *);

int main(int argc, char const *argv[])
{
	dnb op1,op2,sum;

	printf("请输入被加数(0<=x<256)：");
	getdnb(&op1);
	printf("请输入加数(0<=y<256)：");
	getdnb(&op2);
	adder(&op1,&op2,&sum);

	printf("   %9s  \n", op1.binstr);
	printf("  +%9s  \n", op2.binstr);
	printf("----------------------------\n");
	printf("  =%9s  %d\n", sum.binstr, sum.decimal);
	return 0;
}

void eatline() 
{
	while (getchar()!='\n')
		continue;
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;
	ret_val=fgets(st,n,stdin);
	if (ret_val)
	{	
		find=strchr(st,'\n');
		if (find)
		{
			*find='\0';
		} else 
			eatline();
	}
	return ret_val;
}

void d2b(dnb * op)
{
	char temp;

	for (int i=0; i<8; ++i)
	{
		op->bin[i]=op->decimal%2;
		op->decimal=((op->decimal-op->bin[i])/2);

		if (op->bin[i])
			op->binstr[i]='1';
		else
			op->binstr[i]='0';
	}

	for (int i=0; i<4; ++i)
	{
		temp=op->binstr[i];
		op->binstr[i]=op->binstr[7-i];
		op->binstr[7-i]=temp;
	}
	
	op->binstr[8]='\0';
}

void getdnb(dnb * op)
{
	int x=0;
	char input[4];

	while (1) {
		int flag=1,i=0;

		s_gets(input,4);
		
		while (i<3 && input[i]!='\0') {
			if (input[i]<'0' || input[i]>'9')
				flag=0;
			i++;
		}

		if (!flag)
		{
			system("clear");
			printf("输入有误，请重新输入！！！\n");
			continue;
		}

		x=atoi(input);

		if (x<0 || x>=256)
		{
			system("clear");
			printf("超出范围！！！\n");
			continue;
		}
		
		break;
	}
	op->decimal=x;
	d2b(op);
}

int exor(int a, int b)
{
	return (a&&!b || !a&&b);
}

void adder(dnb *x, dnb *y, dnb *s)
{
	int z[9]={0};
	char temp;

	for (int i=0; i<8; ++i)
	{
		s->bin[i]=exor(exor(x->bin[i],y->bin[i]),z[i]);
		z[i+1]=(z[i] && exor(x->bin[i],y->bin[i])) || (x->bin[i] && y->bin[i]);

		if (s->bin[i])
			s->binstr[i]='1';
		else
			s->binstr[i]='0';
	}

	for (int i=0; i<4; ++i)
	{
		temp=s->binstr[i];
		s->binstr[i]=s->binstr[7-i];
		s->binstr[7-i]=temp;
	}

	s->decimal=s->bin[0]+s->bin[1]*2+s->bin[2]*4+s->bin[3]*8+s->bin[4]*16+s->bin[5]*32+s->bin[6]*64+s->bin[7]*128;
	s->binstr[8]='\0';
}