//#include "prime.h"

///*
// * Primality Test | Set 3 (Miller–Rabin)
// * https://www.geeksforgeeks.org/dsa/check-for-prime-number/
// */

//int power(int x, int n, int m)
//{
//	int res = 1;

//	x = x % p;
//	while (n > 0) {
//		if (n & 1)
//			res = (res * x) % m;
//		n = n >> 1;
//		x = (x * x) % p;
//	}
//	return (res);
//}

//bool millerTest(int d, int n)
//{
//	int a = 2 + rand() % (n - 4);
//	int x = power(a, d, n);
//	while (d != n-1) {
//		x = (x * x) % n;
//		d *= 2;
//		if (x == 1)
//			return (false);
//		if (x == n - 1)
//			return (true);
//	}
//	return (false);
//}

//bool isPrime(int n, int k)
//{
//	if (n <= 1 || n == 4)
//		return (false);
//	if (n <= 3)
//		return (true);
//	int d = n-1;
//	while (d % 2 == 0)
//		d /= 2;

//	for (int i = 0; i < k; i++)
//		if (!millerTest(d, n))
//			return (false);
//	return (true);
//}
