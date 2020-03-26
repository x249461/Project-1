#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

int* tabPomoc;
/*******************************************
*                                          *
* MERGE SORT -- SORTOWANIE PRZEZ SCALANIE  *
*                                          *
********************************************/
template<typename Typ>
void scal(Typ *tab, int lewy, int prawy)
{
	for(int i = lewy; i <= prawy; i++) tabPomoc[i] = tab[i];
	int srodek = (lewy+prawy) / 2;
	int i = lewy;
	int j = srodek+1;
	int k = lewy;

	while(i <= srodek && j <= prawy)
	{
		if (tabPomoc[i] < tabPomoc[j])
			tab[k++] = tabPomoc[i++];
		else
			tab[k++] = tabPomoc[j++];
	}
	while(i <= srodek)
		tab[k++] = tabPomoc[i++];
}

template<typename Typ>
void SortowaniePrzezScalanie(Typ *tab, int lewy, int prawy)
{
	if(lewy < prawy)
	{
		int srodek = (lewy+prawy) / 2; // dziele tablice na pół i sortuję przez scalanie
		SortowaniePrzezScalanie(tab, lewy, srodek);
		SortowaniePrzezScalanie(tab, srodek+1, prawy);
		scal(tab, lewy, prawy); //scalam posortowane tablice
	}
}



/***********************************
*                                  *
* QUICK SORT -- SORTOWANIE SZYBKIE *
*                                  *
************************************/   
// funkcja zamiany elemnetów tablicy
template <class Typ>
void exchange (Typ *tab, long i, long j)
{
  Typ temp;
  temp=tab[i];
  tab[i]=tab[j];
  tab[j]=temp;
}

// implemetacja algorytmu quicksort
template <class Typ>
void quicksort(Typ *tab, int lewy, int prawy)
{
	if(prawy <= lewy) return;
	
	int i = lewy - 1, j = prawy + 1, 
	pivot = tab[(lewy+prawy)/2]; //wybieramy punkt odniesienia
	
	while(1)
	{
		//szukam elementu wiekszego lub rownego piwot stojacego
		//po prawej stronie wartosci pivot
		while(pivot>tab[++i]);
		
		//szukam elementu mniejszego lub rownego pivot stojacego
		//po lewej stronie wartosci pivot
		while(pivot<tab[--j]);
		
		//jesli liczniki sie nie minely to zamień elementy ze soba
		//stojace po niewlasciwej stronie elementu pivot
		if( i <= j)
			//funkcja swap zamienia wartosciami tab[i] z tab[j]
			swap(tab[i],tab[j]);
		else
			break;
	}

	if(j > lewy)
	quicksort(tab, lewy, j);
	if(i < prawy)
	quicksort(tab, i, prawy);
}
/************
*           *
* HEAP SORT *
*           *
************/
// Wykonuję częściowe sortowanie kopca                     
template<typename Typ>
void Heapify(Typ *tab, int i, int n) 
{
	int j = i, lewy = 2*i + 1, prawy = 2*i + 2, tmp;
	if ((lewy < n) && (tab[i] < tab[lewy]))
		j = lewy;
	if ((prawy < n) && (tab[j] < tab[prawy]))
		j = prawy;
	if (i != j)
	 {
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		Heapify(tab, j, n);
	}
}

// Tworzę kopiec                                  
template<typename Typ>
void Zbuduj(Typ *tab, int n)
 {
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(tab, n, i);
}

// Wykonuję sortowanie przez kopiec                                
template<typename Typ>
void HeapSort(Typ *tab, int n)
 {
	int tmp;
	Zbuduj(tab, n);
	for (int i = n - 1; i >= 0; i--) // wyciagam po kolei elementy z kopca
	 {
		tmp = tab[i];
		tab[i] = tab[0];
		tab[0] = tmp;
		Heapify(tab, 0, i);
	}
}

/*******************************************
*                                          *
* INTRO SORT -- SORTOWANIE INTROSPEKTYWNE  *
*                                          *
*******************************************/    
// Implentuję sortowanie przez wstawianie -- insertionSort
template <typename Typ>
void insertionSort(Typ *tab, long N)
{
	long i, j;
	Typ temp;
	for (i = 1; i < N; ++i)
	{
		temp = tab[i];
		for (j = i; j > 0 && temp < tab[j - 1]; --j)
			tab[j] = tab[j - 1];
		tab[j] = temp;
	}
}




 
template <class Typ>
void medianOfThree (Typ *tab, long &L, long &R)
{
  if (tab[++L-1]>tab[--R])
    exchange(tab,L-1,R);
  if (tab[L-1]>tab[R/2])
    exchange(tab,L-1,R/2);
  if (tab[R/2]>tab[R])
    exchange(tab,R/2,R);
    exchange(tab,R/2,R-1);
}
template <class Typ>
long partition (Typ *tab, long L, long R)
{
  long i, j;
  if (R>=3)
    medianOfThree(tab,L,R);
  for (i=L, j=R-2; ; )
  {
    for ( ; tab[i]<tab[R-1]; ++i);
    for ( ; j>=L && tab[j]>tab[R-1]; --j);
    if (i<j)
      exchange(tab,i++,j--);
    else break;
  }
  exchange(tab,i,R-1);
  return i;
}
template<typename Typ>
void introSort(Typ* tab, int N, int M)
{
    long i;
	if (M <= 0)
	{
		HeapSort(tab, N);
		return;
	}
	i = partition(tab, 0, N);
	if (i > 9)
		introSort(tab, i, M - 1);
	if (N - 1 - i >9)
		introSort(tab + i + 1, N - 1 - i, M - 1);
}

template <class Typ>
void Hybrid_Introspective_Sort(Typ *tab, long N)
{
	introSort(tab, N, (int)floor(2 * log(N) / log(2)));
	insertionSort(tab, N);
}


int main(){
  int rozmiarytablicy[5]={10000,50000,100000,500000,1000000};
  
  double stopnieposortowania[8]={0, 0.25, 0.50, 0.75, 0.95, 0.99, 0.997, 1}; //gdy wybrano 1, bedzie to odwrotnie posortowana tablica
    for(int i=0;i<5;i++)
    {
      int rozmtablicy=rozmiarytablicy[i];
      for(int j=0; j<8; j++)
      {
	int dokadposortowac=stopnieposortowania[j]*rozmtablicy-1;
	int **tablicatablic = new int*[100];
	  for(int nrtablicy=0; nrtablicy<100; nrtablicy++)
      {
	tablicatablic[nrtablicy]= new int[rozmtablicy];
	 tabPomoc=new int[rozmtablicy];
	for (int k=0; k<rozmtablicy; k++)
    {
	  tablicatablic[nrtablicy][k]=rand()%10000;
	}
	quicksort<int>(tablicatablic[nrtablicy], 0, dokadposortowac);
	if(stopnieposortowania[j]==1)
    {
	  for(int l=0; l<rozmtablicy; l++)
      {
	    tablicatablic[nrtablicy][l]=-tablicatablic[nrtablicy][l];
	  }
	}
 }
      
	//TEST SZYBKOSCI
	//cout<<"Test dla rozmiaru: "<<rozmtablicy<<" i stopnia posortowania: "<<stopnieposortowania[j]<<"\n";
	//Zapis w formacie rozmiar, stopien posortowania, czas w sekundach
	  cout<<rozmtablicy<<",______"<<stopnieposortowania[j]<<",______";
     int M = int(2 * log2(rozmtablicy)); //stała M reprezentująca maksymalną głębokość w introsort
	  double roznica;
	  cout.setf(ios::fixed); //notacja zwykla
	  clock_t start, koniec; 
	  start=clock(); //start mierzenia czasu
	  
	  for(int nrtablicy=0; nrtablicy<100; nrtablicy++)
      {
	    SortowaniePrzezScalanie<int>(tablicatablic[nrtablicy],0,rozmtablicy-1);
       // HeapSort<int>(tablicatablic[nrtablicy], rozmtablicy);
       //introSort<int>(tablicatablic[nrtablicy], 0, rozmtablicy-1);
        quicksort<int>(tablicatablic[nrtablicy], 0, rozmtablicy-1);
		Hybrid_Introspective_Sort<int>(tablicatablic[nrtablicy], rozmtablicy);
      }
	
	  // HeapSort<int>(tablicatablic[0],rozmtablicy);
	   /*for(int i=0;i<rozmtablicy;i++){
	   cout<<tablicatablic[0][i]<<endl;
	  
      }*/
      
	koniec = clock(); //koniec mierzenia czasu
	roznica = (koniec-start)/(double)CLOCKS_PER_SEC;	
	cout << roznica << endl;

    
    /*
    	//wypisanie wyników
    for (int i = 0; i < 100; i++) 
	{
		for (int j = 0; j < rozmtablicy; j++)
			cout << tablicatablic[i][j]  <<" ";
		cout << endl;   
	}*/
      }
    
	}

}
