数据结构中有一个问题，链表后插。

这个操作需要新建节点，自然要用到`new`或者`malloc`关键字。c中较为严谨，在`malloc`后需要判断是否能新建节点成功（`LNode2 *s2=(LNode2*) malloc(sizeof(LNode2));`），当然99.99%是能成功的，除非计算机内存实在不够了...

于是临下班前试着用c++实现一遍，换成类来描述，这个判断自然就变成了
```cpp
    LNode *S = new LNode();
    if (S == nullptr)
        return false;//内存不足分配失败
```
问题就出在这里了。IDE(Clion)提示我"`Condition is always false`"，并且VS好像还不会报出来这个。

因此下来深入了解了一下。C++中`operator new`的行为及其与`malloc`的区别。`new`在实现中会调用`malloc`并且由编译器安插调用构造函数的代码，`malloc`失败返回0，而`new`直接抛异常。但不清楚有没有不抛异常的`new`和不调用构造函数的new这一点。下面结合代码分析一下。

```assembly
19:     CTest *pTest = new CTest(3, 2);
0027652D 6A 08                push        8  
0027652F E8 8D AD FF FF       call        operator new (02712C1h)  ; 默认的operator new
00276534 83 C4 04             add         esp,4  
00276537 89 85 08 FF FF FF    mov         dword ptr [ebp-0F8h],eax  
0027653D C7 45 FC 00 00 00 00 mov         dword ptr [ebp-4],0  
00276544 83 BD 08 FF FF FF 00 cmp         dword ptr [ebp-0F8h],0  
0027654B 74 17                je          main+74h (0276564h)  
0027654D 6A 02                push        2  
0027654F 6A 03                push        3  
00276551 8B 8D 08 FF FF FF    mov         ecx,dword ptr [ebp-0F8h]  
00276557 E8 B4 AE FF FF       call        CTest::CTest (0271410h)  ; 调用构造函数
0027655C 89 85 E8 FE FF FF    mov         dword ptr [ebp-118h],eax  
00276562 EB 0A                jmp         main+7Eh (027656Eh)  
00276564 C7 85 E8 FE FF FF 00 00 00 00 mov         dword ptr [ebp-118h],0  
0027656E 8B 85 E8 FE FF FF    mov         eax,dword ptr [ebp-118h]  
00276574 89 85 14 FF FF FF    mov         dword ptr [ebp-0ECh],eax  
0027657A C7 45 FC FF FF FF FF mov         dword ptr [ebp-4],0FFFFFFFFh  
00276581 8B 8D 14 FF FF FF    mov         ecx,dword ptr [ebp-0ECh]  
00276587 89 4D EC             mov         dword ptr [pTest],ecx  
    20: 
    21:     CTest *pTest2 = new (std::nothrow) CTest(4, 6);
0027658A 68 D0 C2 27 00       push        offset std::nothrow (027C2D0h)  
0027658F 6A 08                push        8  
00276591 E8 63 AC FF FF       call        operator new (02711F9h)  ;多个参数，不抛异常的operator new
00276596 83 C4 08             add         esp,8  
00276599 89 85 F0 FE FF FF    mov         dword ptr [ebp-110h],eax  
0027659F C7 45 FC 01 00 00 00 mov         dword ptr [ebp-4],1  
002765A6 83 BD F0 FE FF FF 00 cmp         dword ptr [ebp-110h],0  
002765AD 74 17                je          main+0D6h (02765C6h)  
002765AF 6A 06                push        6  
002765B1 6A 04                push        4  
002765B3 8B 8D F0 FE FF FF    mov         ecx,dword ptr [ebp-110h]  
002765B9 E8 52 AE FF FF       call        CTest::CTest (0271410h)  ; 调用构造函数
002765BE 89 85 E8 FE FF FF    mov         dword ptr [ebp-118h],eax  
    20: 
    21:     CTest *pTest2 = new (std::nothrow) CTest(4, 6);
002765C4 EB 0A                jmp         main+0E0h (02765D0h)  
002765C6 C7 85 E8 FE FF FF 00 00 00 00 mov         dword ptr [ebp-118h],0  
002765D0 8B 85 E8 FE FF FF    mov         eax,dword ptr [ebp-118h]  
002765D6 89 85 FC FE FF FF    mov         dword ptr [ebp-104h],eax  
002765DC C7 45 FC FF FF FF FF mov         dword ptr [ebp-4],0FFFFFFFFh  
002765E3 8B 8D FC FE FF FF    mov         ecx,dword ptr [ebp-104h]  
002765E9 89 4D E0             mov         dword ptr [pTest2],ecx  
    22: 
    23:     pTest->m_dw1 = 3;
002765EC 8B 45 EC             mov         eax,dword ptr [pTest]  
002765EF C7 00 03 00 00 00    mov         dword ptr [eax],3  
    24:     pTest2->m_dw2 = 5;
002765F5 8B 45 E0             mov         eax,dword ptr [pTest2]  
002765F8 C7 40 04 05 00 00 00 mov         dword ptr [eax+4],5  
    25:     
    26:     
    27:     return 0;
002765FF 33 C0                xor         eax,eax  
    28: }
```

`operator new`的源码：

```cpp
void* __CRTDECL operator new(size_t const size)
{
    for (;;)
    {
        if (void* const block = malloc(size))
        {
            return block;
        }

        if (_callnewh(size) == 0)
        {
            if (size == SIZE_MAX)
            {
                __scrt_throw_std_bad_array_new_length();
            }
            else
            {
                __scrt_throw_std_bad_alloc();
            }
        }

        // The new handler was successful; try to allocate again...
    }
}
```

`operator new`的源码，嗯嗯，果然不可能抛异常，因为异常都被接住了：

```cpp
void* __CRTDECL operator new(size_t const size, std::nothrow_t const&) noexcept
{
    try
    {
        return operator new(size);
    }
    catch (...)
    {
        return nullptr;
    }
}
```
`delete`操作都是一样的，调用了带两个参数的`operator delete`，这个应该也是后来搞出来的一个函数，我印象还比较深。之前在尝试将VS2022编译的`obj`与WDK中lib版CRT库匹配时曾遇到过这个带了两个参数的`delete`找不到匹配的符号，结果用了/Zc:sizedDealloc-开关才避免其生成。

```assembly
   26:  delete(pTest);
013865FF 8B 45 EC             mov         eax,dword ptr [pTest]  
01386602 89 85 E4 FE FF FF    mov         dword ptr [ebp-11Ch],eax  
01386608 6A 08                push        8  
0138660A 8B 8D E4 FE FF FF    mov         ecx,dword ptr [ebp-11Ch]  
01386610 51                   push        ecx  
01386611 E8 3F AA FF FF       call        operator delete (01381055h)  
01386616 83 C4 08             add         esp,8  
    27:  delete(pTest2);
01386619 8B 45 E0             mov         eax,dword ptr [pTest2]  
0138661C 89 85 D8 FE FF FF    mov         dword ptr [ebp-128h],eax  
01386622 6A 08                push        8  
01386624 8B 8D D8 FE FF FF    mov         ecx,dword ptr [ebp-128h]  
0138662A 51                   push        ecx  
0138662B E8 25 AA FF FF       call        operator delete (01381055h)  
01386630 83 C4 08             add         esp,8  
```

在其中调用了带一个参数的`operator delete`：
```assembly
    28: void __CRTDECL operator delete(void* const block, size_t const) noexcept
    29: {
01384FF0 55                   push        ebp  
01384FF1 8B EC                mov         ebp,esp  
    30:     operator delete(block);
01384FF3 8B 45 08             mov         eax,dword ptr [block]  
    30:     operator delete(block);
01384FF6 50                   push        eax  
01384FF7 E8 36 C0 FF FF       call        operator delete (01381032h)  
01384FFC 83 C4 04             add         esp,4  
    31: }
01384FFF 5D                   pop         ebp  
01385000 C3                   ret  
```

结论：可以通过`std::nothrow让new`不抛异常，VS22下的做法是在该`new`函数中用try捕获了异常，并不再抛出，同时让其返回`0`；对于有构造函数的类对象，`new`时都会调用其构造函数，是由编译器自动插入代码的。

最最后，JetBrains有点意思。