/*
A way to iterate all the submasks of a mask backwards (good for dp)
---
Source: Cp algorithms
*/

// m: Principal mask
for (int s=m; s; s=(s-1)&m) {
}
