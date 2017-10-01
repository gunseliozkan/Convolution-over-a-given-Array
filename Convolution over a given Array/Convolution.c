#include <stdio.h>

typedef enum padding{ZERO, SAME, HALF}PaddingType;
int convolution(double inputArr[], int inputArraySize, double kernelArr[], int
kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType
padding);
void addPadding(double inputArr[], int inputArraySize, double outputArr[], int
*outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main()
{
	int i;
	double inputArr[] = {1,2,3,4,5,6,7};
	double kernelArr[] = {1,2,3};
	double outputArr[255];
	int outputArrSize = 0;
	convolution(inputArr, 7, kernelArr, 3, outputArr, &outputArrSize, 2, SAME);
	for(i=0; i<outputArrSize; i++)
		printf("%.2f ", outputArr[i]);
	printf("\n");
	return 0;
}

int convolution(double inputArr[], int inputArraySize, double kernelArr[], int
kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType
padding)
{
	int result;

	double inputArrCpy[255];
	int inputArrCpySize = 0;
	int paddingWidth=0;
	int str=0;
	int o,k;
	int i;

	if(kernelArraySize>inputArraySize)
		result = -1;

	else
	{
		paddingWidth = (kernelArraySize-1)/2;
		*outputArraySize = ((inputArraySize-kernelArraySize+2*paddingWidth)/stride)+1;
		switch(padding)
		{
			case 0:
				addPadding(inputArr, inputArraySize, inputArrCpy, &inputArrCpySize, paddingWidth, zeroPadding);
				break;
			case 1:
				addPadding(inputArr, inputArraySize, inputArrCpy, &inputArrCpySize, paddingWidth, samePadding);
				break;
			case 2:
				addPadding(inputArr, inputArraySize, inputArrCpy, &inputArrCpySize, paddingWidth, halfPadding);
				break;
		}

		for(o=0; o<=*outputArraySize; o++)
		{
			outputArr[o] = 0;
			for(k=0; k<kernelArraySize; k++,str++)
			{
				outputArr[o] += kernelArr[k]*inputArr[str];
			}
			str = (o+1)*stride;
		}
		result = 0;

	}


	return result;
}

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int
*outputArraySize, int paddingWidth, void paddingMethod(double[], int, int))
{

	int i,k; /*i for output array size counter k for input arrray size counter*/
	*outputArraySize = inputArraySize+(paddingWidth*2); /*initialize output array size*/

	/*from index 0 to index (padding width) doesn't bother me FOR NOW*/
	/*and from index(input array size+padding width) to last index doesn't bother me FOR NOW*/
	/*this line just copies input array to output array considering left and right sides of padding*/
	for(i=paddingWidth,k=0; i<*outputArraySize; i++, k++)
	{
		outputArr[i] = inputArr[k];
	}
	paddingMethod(outputArr, *outputArraySize, paddingWidth);

}

void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i;
	/*to do the padding on the left side*/
	for(i=0; i<paddingWidth; ++i)
	{
		outputArr[i]=0.0;
	}
	/*to do the padding on the right side*/
	for(i=outputArraySize-paddingWidth; i<outputArraySize; i++)
	{
		outputArr[i] = 0.0;
	}
}

void samePadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	double first, last; /*first and last variables of the INPUT array*/
	int i;

	first = outputArr[paddingWidth];
	last = outputArr[outputArraySize-paddingWidth-1];

	for(i=0; i<paddingWidth; i++)
	{
		outputArr[i] = first;
	}

	for(i=outputArraySize-paddingWidth; i<outputArraySize; i++)
	{
		outputArr[i] = last;
	}

}

void halfPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	double first, last;
	int i;

	first = outputArr[paddingWidth]/2.0;
	last = outputArr[outputArraySize-paddingWidth-1]/2.0;

	for(i=0; i<paddingWidth; i++)
	{
		outputArr[i] = first;
	}

	for(i=outputArraySize-paddingWidth; i<outputArraySize; i++)
	{
		outputArr[i] = last;
	}
}
