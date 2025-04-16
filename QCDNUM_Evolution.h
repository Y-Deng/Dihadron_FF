#pragma once

#include "QCDNUM/QCDNUM.h"

static double Flavor_mixing_matrix[] = 
    //tb  bb  cb  sb  ub  db  g   d   u   s   c   b   t
    { 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0.,      // 1=d
      0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0., 0.,      // 2=u
      0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0., 0.,      // 3=s
      0., 0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0.,      // 4=dbar
      0., 0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0.,      // 5=ubar
      0., 0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0.,      // 6=sbar
      0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0., 0.,      // 7=cval
      0., 0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,      // 8=cbar
      0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 1., 0.,      // 9=zero
      0., 1., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,      //10=zero
      0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,      //11=zero
      0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};     //12=zero


int QCDevol_init(const double r20, const double alpha_s0, const double Q20, const double q2thre[3])
{
    int         lun = -6;                                       //输出的控制代码，6为打印到标准输出，-6为抑制输出
    string        s = " ";                                      //输出的文件名，当lun = 6或-6时，无效
    QCDNUM::qcinit(lun, s);                                     //初始化
    //------------------------------------------------------------------------------------
    double  xmin[] = {1.e-3};                                   //x的最小值
    int     iwt[]  = {1};                                       //integer weight
    int        ngx = 1;                                         //xmin 和 iwt的数目
    int       nxin = 100;                                       //请求的格点数
    int       iosp = 3;                                         // spline interpolation. 2 = linear ，3 = quadratic
    int      nxout;                                             //生成的格点数，可能与nxin略有不同。
    QCDNUM::gxmake(xmin,iwt,ngx,nxin,nxout,iosp);               //x-grid
    //------------------------------------------------------------------------------------
    double  qq[] = {  1., 1.e6};                                //定义指定的mu^2，第一个数和最后一个数分别代表mu^2的最小和最大值。
    double  wt[] = {1.e0, 1.e1};                                //定义被指定的子区间的点密度。
    int      ngq = 2;                                           //qq 和 wt 的设定的数目
    int     nqin = 150;                                         //请求的格点数
    int    nqout;                                               //生成的格点数
    QCDNUM::gqmake(qq, wt, ngq, nqin, nqout);                   //mu2-grid
    //------------------------------------------------------------------------------------
    int       itype = 3;
    int       id1_f, id2_f;                                     //过时参数
    int       nw_f;                                             //Total number of words used in memory.
    QCDNUM::fillwt(itype, id1_f, id2_f, nw_f);                  //calculate weights
    //------------------------------------------------------------------------------------
    double  q2c = q2thre[0], q2b = q2thre[1], q2t = q2thre[2];
    int iqc  = QCDNUM::iqfrmq(q2c);                             //charm threshold
    int iqb  = QCDNUM::iqfrmq(q2b);                             //bottom threshold
    int iqt  = QCDNUM::iqfrmq(q2t);                             //top threshold
    //------------------------------------------------------------------------------------
    int iord = 2; 
    QCDNUM::setalf(alpha_s0, r20);                              //input alphas
    QCDNUM::setcbt(0, iqc, iqb, iqt);                           //thresholds in the VFNS    
    int iq0  = QCDNUM::iqfrmq(Q20);                             //找到初始能标对应的格点
    QCDNUM::setord(iord);
    QCDNUM::setval("elim",-1);

    return iq0;
}