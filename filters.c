#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            double sum=image[i][j].rgbtRed +image[i][j].rgbtBlue +image[i][j].rgbtGreen;
            double avg=round(sum/3.0);
            image[i][j].rgbtRed =avg;
            image[i][j].rgbtBlue =avg;
            image[i][j].rgbtGreen =avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int loop;
    BYTE temp;
        if (width%2==0)
        loop= width /2;
        else
        loop = (width-1)/2;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<loop;j++)
        {
            temp=image[i][j].rgbtRed;
            image[i][j].rgbtRed=image[i][width-1-j].rgbtRed;
            image[i][width-1-j].rgbtRed=temp;
            
            temp=image[i][j].rgbtGreen;
            image[i][j].rgbtGreen=image[i][width-1-j].rgbtGreen;
            image[i][width-1-j].rgbtGreen=temp;
            
            temp=image[i][j].rgbtBlue;
            image[i][j].rgbtBlue=image[i][width-1-j].rgbtBlue;
            image[i][width-1-j].rgbtBlue=temp;
        }
    }    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i_temp;
    int j_temp;
    double count;
    double sumR;
    double sumB;
    double sumG;
    RGBTRIPLE image2[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            i_temp=i-1;
            j_temp=j-1;
            count=0;
            sumR=0;
            sumB=0;
            sumG=0;
            for(int i1=0;i1<3;i1++)
            {
                    for(int j1=0;j1<3;j1++)
                    {
                        if(i_temp>=0 && j_temp>=0 && i_temp<=(height-1) && j_temp<=(width-1))
                         {
                              count++;
                              sumR = sumR + image[i_temp][j_temp].rgbtRed;
                              sumG = sumG + image[i_temp][j_temp].rgbtGreen;
                              sumB = sumB + image[i_temp][j_temp].rgbtBlue;
                         }
                           j_temp++;
                    }
                    i_temp++;
                    j_temp = j-1;
            }
                if(count!=0)
                {
                image2[i][j].rgbtRed = round(sumR/count);
                image2[i][j].rgbtGreen = round(sumG/count);
                image2[i][j].rgbtBlue = round(sumB/count);
                }
        }
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
                image[i][j].rgbtRed = image2[i][j].rgbtRed;
                image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
                image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i_temp;
    int j_temp;
    double count;
    double GxB,GyB;
    double GxG,GyG;
    double GxR,GyR;
    RGBTRIPLE image2[height][width];
    int Gmatrix [3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            i_temp=i-1;
            j_temp=j-1;
            GxB=0; GyB=0;
            GxR=0; GyR=0;
            GxG=0; GyG=0;
            
            for(int i1=0;i1<3;i1++)
            {
                    for(int j1=0;j1<3;j1++)
                    {
                        if(i_temp>=0 && j_temp>=0 && i_temp<=(height-1) && j_temp<=(width-1))
                         {
                              GxR = GxR + (image[i_temp][j_temp].rgbtRed * Gmatrix[i1][j1]);
                              GyR = GyR + (image[i_temp][j_temp].rgbtRed * Gmatrix[j1][i1]);
                              
                              GxB = GxB + (image[i_temp][j_temp].rgbtBlue * Gmatrix[i1][j1]);
                              GyB = GyB + (image[i_temp][j_temp].rgbtBlue * Gmatrix[j1][i1]);
                              
                              GxG = GxG + (image[i_temp][j_temp].rgbtGreen * Gmatrix[i1][j1]);
                              GyG = GyG + (image[i_temp][j_temp].rgbtGreen * Gmatrix[j1][i1]);
                         }
                           j_temp++;
                    }
                    i_temp++;
                    j_temp = j-1;
            }
            
            if(round(sqrt(pow(GxR,2.0)+pow(GyR,2.0)))>255)
            image2[i][j].rgbtRed=255;
            else
            image2[i][j].rgbtRed = round(sqrt(pow(GxR,2.0)+pow(GyR,2.0)));
            
            if(round(sqrt(pow(GxG,2.0)+pow(GyG,2.0)))>255)
            image2[i][j].rgbtGreen=255;
            else
            image2[i][j].rgbtGreen = round(sqrt(pow(GxG,2.0)+pow(GyG,2.0)));
            
            if(round(sqrt(pow(GxB,2.0)+pow(GyB,2.0)))>255)
            image2[i][j].rgbtBlue=255;
            else
            image2[i][j].rgbtBlue = round(sqrt(pow(GxB,2.0)+pow(GyB,2.0)));
                            
        }
    }
    
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
                image[i][j].rgbtRed = image2[i][j].rgbtRed;
                image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
                image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
        }
    }
    return;
}
