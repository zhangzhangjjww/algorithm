int maximum(int a1,int a2,int a3)
{
    if(a1>=a2&&a1>=a3)
        return a1;
    if(a2>=a1&&a2>=a3)
        return a2;
    if(a3>=a1&&a3>=a2)
    return a3;
}
int maximum(int a1,int a2)
{
    if(a1>=a2)
        return a1;
    return a2;
}
