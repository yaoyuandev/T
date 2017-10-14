for(int i=2;i<=m+1;++i)  
{  
    s[i][n+1]=n;  
    for(int j=n;j>i;--j)  
    {  
        for(int k=s[i-1][j];k<=s[i][j+1];++k)  
        {  
            LL tmp=dp[i-1][k]+w[k+1][j];  
    //      cout<<i<<' '<<j<<' '<<k<<' '<<tmp<<endl;  
            if(tmp<dp[i][j])  
            {  
                dp[i][j]=tmp;  
                s[i][j]=k;  
            }  
        }  
    }  
}  
