#include <iostream.h>

void move(char source, char target, int N, char tmp)
// This is a recursive function.
{
 if (N == 1)
    cout << "Move disk from " << source << " to " << target << "\n"; 
 else
 {
    move(source, tmp, N-1, target);
    cout << "Move disk from " << source << " to " << target << "\n";
    move(tmp, target, N-1, source);
 }
}

void main()
{
    int N;
    cout << "\n\n Enter number of disks: ";
    cin >> N;
    move('A','B', N,'C');
    getchar();
}


