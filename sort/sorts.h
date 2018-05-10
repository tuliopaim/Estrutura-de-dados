#define RANGE 1000


//-----------------------------
//BIBLIOTECA
//TRABALHO DE TULIO PAIM E BRUNO ROCHA
//SORTS
//-----------------------------

//ESTRUTURA HEAP

typedef struct HEAP{
  int size;
  int length;
  int * values;
}heap;


void merge(int * arr, int l, int m, int r);
void mergeSort (int * arr , int l, int r);
void bubbleSort (int * arr , int size);
void selectionSort(int * vetor, int size);
void selectionSort2(int * arr , int size);
void insertionSort(int * arr , int size);
void merge(int * arr, int l, int m, int r);
void mergeSort (int * arr , int l, int r);
int partition(int * arr, int l, int h);
void quickSort(int * arr, int l, int h);
void countingSort(int * arr, int size);
void countSort(int * arr, int size, int exp);
void radixSort(int * arr, int size);
heap * heap_start(int size);
void heap_up(heap * h);
void heap_down(heap * h, int i);
void heap_insert(heap * h, int value);
int get_parent(int i);
void heap_remove(heap * h, int value);
void heap_sort(int * numeros, int size);


//BUBBLE
//------------------------

void bubbleSort (int * arr , int size)
{

	/*
	* Função de ordenação Bubble Sort
	* @param endereço do array
	* @param tamanho do array
	*/

	int temp;
	int iCount, jCount;

	printf ("Metodo: Bubble Sort\n");

	for (iCount = 0 ; iCount < size ; iCount++)
	{
		for (jCount = 0 ; jCount < size - iCount - 1 ; jCount++)
		{
			if (arr[jCount] > arr[jCount + 1])
			{
			temp = arr[jCount + 1];
			arr[jCount + 1] = arr[jCount];
			arr[jCount] = temp;
			}
		}
	}
}

//INSERTION
//----------------------------

void insertionSort (int * arr , int size)
{

	/*
	* Função de ordenação Insertion Sort
	* @param endereço do array
	* @param tamanho do array
	*/

	int temp;
	int iCount, jCount;

	for (iCount = 1 ; iCount < size ; iCount++)
	{
		temp = arr[iCount];
		jCount = iCount - 1;
		while (jCount >= 0 && arr[jCount] > temp)
		{
			arr[jCount + 1] = arr[jCount];
			jCount--;
		}
		arr[jCount + 1] = temp;
	}

	return ;
}

//SELECTION
//-----------------------

void selectionSort(int * vetor, int size){
	int temp;
	int i, j;
	for (i = 0; i < size-1; ++i){
		for (j = i+1; j < size; ++j){
			if(vetor[i] > vetor [j]){
				temp = vetor[i];
				vetor[i] = vetor[j];
				vetor[j] = temp;
			}
		}
	}

}

//SELECTION OTIMIZADO
//-------------------------

void selectionSort2(int * arr , int size)
{

	/*
	* Função de ordenação Selection Sort
	* @param endereço do array
	* @param tamanho do array
	*/

	int min, temp;
	int iCount, jCount;

	printf("Metodo: Selection Sort\n");

	for (iCount = 0 ; iCount < size - 1 ; iCount++)
	{
		min = iCount;

		for (jCount = iCount + 1 ; jCount < size; jCount++)
		{
			if (arr[jCount] < arr[min])
				min = jCount;
		}

		if (min != iCount)
		{
			temp = arr[iCount];
			arr[iCount] = arr[min];
			arr[min] = temp;
		}
	}
}

//MERGE
//-----------------------

void merge(int * arr, int l, int m, int r){

	int n1 = m - l;
	int n2 = r- m;
	int i;

	int L[n1], R[n2];

	//PASSAR VETOR PARA ESQUERDA E DIREITA
	for(i=0;i<n1;i++)
		L[i] = arr[l+i];
	for(i=0;i<n2;i++)
		R[i] = arr[m+1+i];

	i = 0; //indice L[]
	int j = 0; //indice R[]
	int k = l; //indice arr[]

	//VERIFICAR O MAIOR E PASSAR PRO ARR
	while(i < n1 && j < n2){
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	//ADD O QUE SOBRAR DOS VETORES
	while(i < n1){
		arr[k] = L[i];
		i++;k++;
	}

	while(j < n2){
		arr[k] = R[j];
		j++;k++;
	}
}

void mergeSort (int * arr , int l, int r){

	if(l<r){
		int m = l + (r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

//QUICK
//------------------------

int partition(int * arr, int l, int h){
	int pivot = arr[h];
	int i = (l-1);
	int temp;

	for(int j=l;j<=h-1;j++){
		if(arr[j] <= pivot){
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[i+1];
	arr[i+1] = arr[h];
	arr[h] = temp;
	return (i+1);
}


void quickSort(int * arr, int l, int h){
	if(l<h){
		int pi = partition(arr, l , h);
		quickSort(arr, l, pi-1);
		quickSort(arr, pi+1, h);
	}
}

//COUNTING
//------------------------

void countingSort(int * arr, int size){
	int aux[size];
	int count[RANGE+1]={0};
	int i;

	//ARMAZENAR QUANTIDADE DE CADA NUMERO
	for(i=0;i<size;++i)
		count[arr[i]]+=1;
	//SOMAR COM POSIÇÃO ANTERIOR PARA OBTER A POSICAO
	for(i=1;i<RANGE;++i)
		count[i]+=count[i-1];
	//COLOCAR OS NUMEROS EM ORDEM NO VETOR AUX
	for(i=0;i<size;i++){
		aux[count[arr[i]]-1] = arr[i];
		--count[arr[i]];
	}
	//PASSAR PRO VETOR ORIGINAL ORDENADO
	for(i=0;i<size;++i)
		arr[i]=aux[i];
}

// RADIX
//--------------------------

void countSort(int * arr, int size, int exp){
	int aux[size];
	int count[RANGE+1];
	int i;

	//ZERAR VETOR COUNT
	memset(count, 0, sizeof(count));

	//ARMAZENAR QUANTIDADE DE CADA NUMERO
	for(i=0;i<size;++i)
		count[(arr[i]/exp)%10]+=1;
	//SOMAR COM POSIÇÃO ANTERIOR PARA OBTER A POSICAO
	for(i=1;i<RANGE;++i)
		count[i]+=count[i-1];
	//COLOCAR OS NUMEROS EM ORDEM NO VETOR AUX
	for(i=0;i<size;i++){
		aux[count[(arr[i]/exp)%10]-1] = arr[i];
		--count[(arr[i]/exp)%10];
	}
	//PASSAR PRO VETOR ORIGINAL ORDENADO
	for(i=0;i<size;++i)
		arr[i]=aux[i];
}

void radixSort(int * arr, int size){

	//ACHAR O VALOR MAXIMO DO VETOR
	int m = arr[0];
	for(int i=0;i<size;i++)
		if(arr[i] > m)
			m = arr[i];
	//FAZER O COUNTING PRA CADA DIGITO
	for(int exp=1; m/exp > 0; exp*=10)
		countSort(arr, size, exp);

}

//BUCKET
//---------------------------------------

void bucketSort(int * arr, int size, int qnt_baldes){
	int i,j,k;
	int min = arr[0], max = arr[0];
	int *balde[qnt_baldes], qntNumeroBalde[qnt_baldes], alocadosBalde[qnt_baldes];
	int tamanhoBalde = 0;
	for (i = 0; i < qnt_baldes; ++i){
		alocadosBalde[i] = 1;
		qntNumeroBalde[i] = 0;
		balde[i] = malloc(sizeof(int) * alocadosBalde[i]);
	}

	for (i = 0; i < size; ++i){
		min = min < arr[i] ? min : arr[i];
		max = max > arr[i] ? max : arr[i];
	}

	tamanhoBalde = ((max - min) / (float)qnt_baldes) + 0.5f;

	for(i = 0; i < size; ++i){
		for (j = 0; j < qnt_baldes; ++j){
			if(min + (tamanhoBalde * (j + 1)) - 1 < arr[i] && j + 1 < qnt_baldes) continue;
			if(alocadosBalde[j] <= qntNumeroBalde[j]){
				alocadosBalde[j] *= 2;
				balde[j] = realloc(balde[j], sizeof(int) * alocadosBalde[j]);
			}
			balde[j][qntNumeroBalde[j]++] = arr[i];
			break;
		}
	}


	k = 0; // Posição no Array final
	for (i = 0; i < qnt_baldes; ++i){
		insertionSort(balde[i], qntNumeroBalde[i]);
		for (j = 0; j < qntNumeroBalde[i]; ++j){
			arr[k++] = balde[i][j];
		}
	}
}


//HEAP SORT

void heap_sort(int * numeros, int size){
  heap * h = heap_start(size);
  for(int i = 0; i < size; i++){
    heap_insert(h,numeros[i]);
  }
  for(int i = 0; i < size; i++){
    //printf("\n\n");
    //heap_print(h,0,0);
    int valor = h->values[0];
    h->values[0] = h->values[h->length-1];
    h->values[--(h->length)] = -1;
    heap_down(h,0);
    numeros[i] = valor;
  }
}

heap * heap_start(int size){
  heap * h = malloc(sizeof(heap));
  h->size = size;
  h->length = 0;
  h->values = malloc(sizeof(int) * size);
  return h;
}
void heap_insert(heap * h, int value){

  if(h->length >= h->size) return;

  h->values[h->length++] = value;

  heap_up(h);

}

int get_parent(int i){
  return (i-1)/2;
}

void heap_up(heap * h){
  int i = h->length-1;
  int parent = get_parent(i);

  while( i > 0 && (h->values[i] < h->values[parent]) ){
    //SWAP
    int temp = h->values[i];
    h->values[i] = h->values[parent];
    h->values[parent] = temp;

    i = parent;
    parent = get_parent(i);
  }
}
void heap_down(heap * h, int pai){
  int filho;
  if(h->values[2*pai+1] > h->values[2*pai+2])
    filho = 2*pai+1;
  else
    filho = 2*pai+2;

  while(filho <= h->length-1 && (h->values[pai] > h->values[filho])){

    //SWAP
    int temp = h->values[pai];
    h->values[pai] = h->values[filho];
    h->values[filho] = temp;

    pai = filho;

    if(h->values[2*pai+1] > h->values[2*pai+2])
      filho = 2*pai+1;
    else
      filho = 2*pai+2;
  }
}
