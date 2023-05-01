 
#include <iostream>
 
using namespace std;
 
 
 
//Function Declarations
 
void mergeSort(int numbers[], int temp[], int array_size);
 
void m_sort(int numbers[], int temp[], int left, int right);
 
void merge(int numbers[], int temp[], int left, int mid, int right);
 
 
 
int main()
 
{
 
        int arrayOne[5] = {65, 72, 105, 55, 2};
 
        int arrayTwo[5];
 
 
 
        mergeSort(arrayOne, arrayTwo, 5);
 
 
 
        for (int i = 0; i < 5; i++)
 
        {
 
                cout << arrayOne[i] << " ";
 
        }//end for
 
 
 
        return 0;
 
}//end main
 
 
 
 
 
// "Main" function of the sequence
 
// From here on out everything is called recursively
 
void mergeSort(int numbers[], int temp[], int array_size)
 
{
 
  m_sort(numbers, temp, 0, array_size - 1);
 
}
 
 
 
 
 
void m_sort(int numbers[], int temp[], int left, int right)
 
{
 
  int mid;
 
 
 
  if (right > left)
 
  {
 
    mid = (right + left) / 2;
 
    m_sort(numbers, temp, left, mid);
 
    m_sort(numbers, temp, (mid+1), right);
 
 
 
    merge(numbers, temp, left, (mid+1), right);
 
  }
 
}
 
 
 
void merge(int numbers[], int temp[], int left, int mid, int right)
 
{
 
  int i, left_end, num_elements, tmp_pos;
 
 
 
  left_end = (mid - 1);
 
  tmp_pos = left;
 
  num_elements = (right - left + 1);
 
 
 
  while ((left <= left_end) && (mid <= right))
 
  {
 
    if (numbers[left] <= numbers[mid])
 
    {
 
      temp[tmp_pos] = numbers[left];
 
      tmp_pos += 1;
 
      left += 1;
 
    }
 
    else
 
    {
 
      temp[tmp_pos] = numbers[mid];
 
      tmp_pos += 1;
 
      mid += 1;
 
    }
 
  }
 
 
 
  while (left <= left_end)
 
  {
 
    temp[tmp_pos] = numbers[left];
 
    left += 1;
 
    tmp_pos += 1;
 
  }
 
  while (mid <= right)
 
  {
 
    temp[tmp_pos] = numbers[mid];
 
    mid += 1;
 
    tmp_pos += 1;
 
  }
 
 
 
  //modified
 
  for (i=0; i < num_elements; i++)
 
  {
 
    numbers[right] = temp[right];
 
    right -= 1;
 
  }
 
}
