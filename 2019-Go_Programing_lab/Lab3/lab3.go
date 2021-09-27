package main

import "fmt"

func Sum(n int64) int64 {
	var ans int64
	var i int64
	ans = 1
	fmt.Print("1")
	for i = 2; i <= n; i++ {
		if i%7 == 0 {
			continue

		} else {
			ans += i
			fmt.Print("+", i)
		}
	}
	fmt.Print("=")
	return ans
}

func main() {
	// Please complete the code to make this program be compiled without error.
	// Notice that you can only add code in this file.
	var n int64
	for true {
		fmt.Scanln(&n)
		if n <= 0 {
			break
		} else if n > 10000 {
			fmt.Println("n>10000")
		} else {
			fmt.Println(Sum(n))
		}

	}
}
