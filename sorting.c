#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
void bubble_sort(int a[],int n);
void selection_sort(int a[],int n);
void insertion_sort(int a[],int n);
void myinsertion_sort(int a[],int n);
void merge_sort(int a[],int low,int high);
void quick_sort(int a[],int low,int high);
int partition(int a[],int low,int high);
void shell_sort(int a[],int n);
void bucket_sort(int a[],int n);
void radix_sort(int a[],int n);
void count_sort(int a[],int n);
void count_sort1(int a[],int n);
void count_sort2(int a[],int n,int pos);
void merge(int a[],int low,int mid,int high);
int find_max(int a[],int n);
void swap(int *p,int *q);
int main() {
	int a[20],n;
	printf("Enter no of elements\n");
	scanf("%d",&n);
	printf("Enter the elements into the arary\n");
	for (int i = 0; i < n; i++)
	{
	scanf("%d",&a[i]);
	}
	// bubble_sort(a,n);
	// selection_sort(a,n);
	// insertion_sort(a,n);
	// merge_sort(a,0,n-1);
	// count_sort1(a,n);
    radix_sort(a,n);
    // quick_sort(a,0,n-1);
	// myinsertion_sort(a,n);
    shell_sort(a,n);
	printf("Elements after sort are\n");
	for (int i = 0; i < n; i++)
	{
	printf("%3d",a[i]);
	}

	return 0;
}
void bubble_sort(int a[],int n) {
	int temp;
	for (int i = 0; i < n-1; i++)
	{
	  for (int j = 0; j < n-i-1; j++)
	  {
		if (a[j]>a[j+1])
		{
			temp=a[j];
			a[j]=a[j+1];
			a[j+1]=temp;
		}
	  }
	}
}
void selection_sort(int a[],int n) {
	int i,j,min,temp;
	for(i=0;i<n-1;i++) {
		min=i;
		for(j=i+1;j<n;j++) {
			if(a[j]<a[min]) {
				min=j;
			}
		}
		if (min!=i) {
			temp=a[i];
			a[i]=a[min];
			a[min]=temp;
		}
	}
}
void insertion_sort(int a[],int n) {
	int temp,j;
	for(int i=1;i<n;i++) {
		temp=a[i];
		j=i;
		while((j>0)&&(a[j-1]>temp)) {
			a[j]=a[j-1];
			j--;
		}
		a[j]=temp;
	}
}
void myinsertion_sort(int a[],int n) {
	int temp;
	for(int i=1;i<n;i++) {
		for(int j=i-1;j>=0;j--) {
			if (a[j]>a[j+1]) {
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
void merge_sort(int a[],int low,int high) {
	if (low<high)
	{
         int mid=(high+low)/2;
         merge_sort(a,low,mid);
         merge_sort(a,mid+1,high);
		 merge(a,low,mid,high);
	}
}
void merge(int a[],int low,int mid,int high) {
	int i,j,k,b[20];
	i=low;
	j=mid+1;
	k=low;
	while ((i<=mid)&&(j<=high))
	{
		if(a[i]<a[j]) {
			b[k++]=a[i++];
		}
		else {
			b[k++]=a[j++];
		}
	}
	while (i<=mid)
	{
		b[k++]=a[i++];
	}
	while (j<=high) {
		b[k++]=a[j++];
	}
	for (int i = low; i <=high; i++)
	{
	a[i]=b[i];
	}
}
int find_max(int a[],int n) {
	int max=INT_MIN;
	for (int i = 0; i < n; i++)
	{
		if (a[i]>max)
		{
			max=a[i];
		}
	}
	return max;
}
void count_sort(int a[],int n) {
	int i,j,max,*b;
	max=find_max(a,n);
    b=(int *)malloc(sizeof(int)*(max+1));
	for(int i=0;i<max+1;i++) {
		b[i]=0;
	}
	for (int i=0;i<n;i++) {
		b[a[i]]++;
	}
    i=0,j=0;
	while (j<max+1) {
		if (b[j]>0) {
			a[i++]=j;
			b[j]--;
		}
		else
		j++;
	}
}
void count_sort1(int a[],int n) {
	int i,j,max,output[n];
	max=find_max(a,n);
  int b[max+1];
	for(int i=0;i<max+1;i++) {
		b[i]=0;
	}
	for (int i=0;i<n;i++) {
		b[a[i]]++;
	}
	for (int i=1;i<max+1;i++) {
		b[i]+=b[i-1];
	}
	for (int i=n-1;i>=0;i--) {
		output[--b[a[i]]] = a[i];
	}
	for (int i=0;i<n;i++) {
		a[i]=output[i];
	}
}
void count_sort2(int a[],int n,int pos) {
   int new[n];
   int count[10]={ 0 };
   for(int i=0;i<n;i++) 
    count[(a[i]/pos)%10]++;
   for(int i=1;i<10;i++)
    count[i]+=count[i-1];
   for(int i=n-1;i>=0;i--) 
    new[--count[((a[i]/pos)%10)]]=a[i];
   for(int i=0;i<n;i++) 
    a[i]=new[i];
}
void radix_sort(int a[],int n) {
    int max=find_max(a,n);
    for(int pos=1;max/pos>0;pos*=10) {
        count_sort2(a,n,pos);
    }
}
void swap(int *p,int *q) {
    int temp=*p;
    *p=*q;
    *q=temp;
}
int partition(int a[],int low,int high) {
int pivot=a[low];
int i=low,j=high;
while(i<j) {
    while ((a[i]<=pivot)&&(i<high)) {
        i++;
    }
    while((a[j]>pivot)&&(j>low)) {
        j--;
    }
    if(i<j) {
        swap(&a[i],&a[j]);
    }
}
swap(&a[low],&a[j]);
return j;
}
void quick_sort(int a[],int low,int high) {
    int j;
    if(low<high) {
        j=partition(a,low,high);
        quick_sort(a,low,j);
        quick_sort(a,j+1,high);
    }
}
void shell_sort(int a[],int n) {
    for (int gap=n/2;gap>0;gap/=2) {
        for(int i=gap;i<n;i++) {
            int temp=a[i];
            int j=i-gap;
            while((j>=0)&&(a[j]>temp)) {
                a[j+gap]=a[j];
                j=j-gap;
            }
            a[j+gap]=temp;
        }
    }
}
//algorithm for insertion sort in linked list
// function InsertionSort(Node head)
//     Node sorted = NULL
//     Node curr = head
//     while curr != NULL
//         Node currNext = curr.next
//         SortedInsert(sorted ,curr)
//         curr = currNext
//     end while
//     head = sorted 
// end function

// function SortedInsert(Node sorted, Node new_node)
//     If sorted == NULL or sorted.data > new_node.data
//         new_node.next = sorted 
//         sorted = new_node
//     end if
//     else
//         Node curr = sorted 
//         while curr.next != NULL and curr.next.data <= new_node.data
//             curr = curr.next
//         end while
//         new_node.next = curr.next
//         curr.next = new_node
//     end else
// end function




// // Bucket sort in C
// #include <stdio.h>
// #include <stdlib.h>

// #define NARRAY 7   // Array size
// #define NBUCKET 100  // Number of buckets
// #define INTERVAL 10  // Each bucket capacity

// struct Node {
//   int data;
//   struct Node *next;
// };

// void BucketSort(int arr[],int N);
// struct Node *InsertionSort(struct Node *list);
// void SortedPush(struct Node **head, struct Node *newListNode);
// void print(int arr[],int N);
// void printBuckets(struct Node *list);
// int getBucketIndex(int value);

// // Sorting function
// void BucketSort(int arr[],int N) {
//   int i, j;
//   struct Node **buckets;

//   // Create buckets and allocate memory size
//   buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

//   // Initialize empty buckets
//   for (i = 0; i < NBUCKET; ++i) {
//     buckets[i] = NULL;
//   }

//   // Fill the buckets with respective elements
//   for (i = 0; i < N; ++i) {
//     struct Node *current;
//     int pos = getBucketIndex(arr[i]);
//     current = (struct Node *)malloc(sizeof(struct Node));
//     current->data = arr[i];
//     current->next = buckets[pos];
//     buckets[pos] = current;
//   }

//   // Print the buckets along with their elements
//   for (i = 0; i < NBUCKET; i++) {
//     printf("Bucket[%d]: ", i);
//     printBuckets(buckets[i]);
//     printf("\n");
//   }

//   // Sort the elements of each bucket
//   for (i = 0; i < NBUCKET; ++i) {
//     buckets[i] = InsertionSort(buckets[i]);
//   }

//   printf("-------------\n");
//   printf("Buckets after sorting\n");
//   for (i = 0; i < NBUCKET; i++) {
//     printf("Bucket[%d]: ", i);
//     printBuckets(buckets[i]);
//     printf("\n");
//   }

//   // Put sorted elements on arr
//   for (j = 0, i = 0; i < NBUCKET; ++i) {
//     struct Node *node;
//     node = buckets[i];
//     while (node) {
//       arr[j++] = node->data;
//       node = node->next;
//     }
//   }

//   return;
// }

// // Function to sort the elements of each bucket
// struct Node *InsertionSort(struct Node *head) {
//   if (head == 0 || head->next == 0) {
//     return head;
//   }
//    struct Node *sortedList = NULL;

//     /* Travel given list and insert every node in sorted list at it's correct position */
//     struct Node *curr = head;
//     while (curr != NULL)
//     {
//         // Store the next node of curr for next iteration
//         struct Node *next = curr->next;
//         // Inserting current in sorted linked list
//         SortedPush(&sortedList, curr);
//         // Updating current
//         curr = next;
//     }
//     /* Update head to point to the sorted list */
//     head = sortedList;
//   return head;
// }
// void SortedPush(struct Node **head, struct Node *newListNode)
// {
//     // current node
//     struct Node *curr;

//     if (*head == NULL || (*head)->data > newListNode->data)
//         newListNode->next = *head, *head = newListNode;
//     else
//     {
//         // Need to locate the correct place to insert ListNode in the sorted linked list
//         curr = *head;
//         while (curr->next != NULL && curr->next->data <= newListNode->data)
//             curr = curr->next;
//         newListNode->next = curr->next, curr->next = newListNode;
//     }
// }

// int getBucketIndex(int value) {
//   return value / INTERVAL;
// }

// void print(int ar[],int N) {
//   int i;
//   for (i = 0; i < N; ++i) {
//     printf("%d ", ar[i]);
//   }
//   printf("\n");
// }

// // Print buckets
// void printBuckets(struct Node *list) {
//   struct Node *cur = list;
//   while (cur) {
//     printf("%d ", cur->data);
//     cur = cur->next;
//   }
// }

// // Driver code
// int main(void) {
//   int N;
//   printf("Enter no of elements\n");
//   scanf("%d",&N);
//   int array[N];
//   printf("Enter the elements into the arary\n");
//   for (int i = 0; i < N; i++)
// 	{
// 	scanf("%d",&array[i]);
// 	}

//   printf("Initial array: ");
//   print(array,N);
//   printf("-------------\n");

//   BucketSort(array,N);
//   printf("-------------\n");
//   printf("Sorted array: ");
//   print(array,N);
//   return 0;
// }
// //algorithm for insertion in linked list
// // function InsertionSort(Node head)
// //     Node sorted = NULL
// //     Node curr = head
// //     while curr != NULL
// //         Node currNext = curr.next
// //         SortedInsert(sorted ,curr)
// //         curr = currNext
// //     end while
// //     head = sorted 
// // end function

// // function SortedInsert(Node sorted, Node new_node)
// //     If sorted == NULL or sorted.data > new_node.data
// //         new_node.next = sorted 
// //         sorted = new_node
// //     end if
// //     else
// //         Node curr = sorted 
// //         while curr.next != NULL and curr.next.data <= new_node.data
// //             curr = curr.next
// //         end while
// //         new_node.next = curr.next
// //         curr.next = new_node
// //     end else
// // end function









