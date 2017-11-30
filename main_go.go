package main

import (
	"fmt"
)

type MyError struct {
	msg string
}

func (p MyError) Error() string {
	return p.msg
}

type Dispatcher interface {
	Dispatch() error
}

type T1 struct {
	name string
}

func MakeT1(name string) T1 {
	return T1{name}
}

func (p T1) Dispatch() error {
	fmt.Printf("%v\n", p.name)

	return nil
}

type T2 struct {
	id int
}

func MakeT2(id int) T2 {
	return T2{id}
}

func (p T2) Dispatch() error {
	fmt.Printf("%v\n", p.id)

	return MyError{"something failed"}
}

func main() {
	var objs []Dispatcher
	objs = append(objs, MakeT1("Hi there!"))
	objs = append(objs, MakeT2(42))

	for i := range objs {
		MyError := "ok"
		if err := objs[i].Dispatch(); err != nil {
			MyError = err.Error()
		}
		fmt.Printf("obj %v dispatched %v\n", i, MyError)
	}
}
