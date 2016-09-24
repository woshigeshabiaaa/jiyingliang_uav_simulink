clearvars UAV Mixer
UAV=struct('Is',eye(3),'Is_inv',eye(3),'Mass',10,'L',1,'AllocationMoment',0,'RotorNum',0,'Type',[],'AllocationRotate',0,'GravityAcc',9.81,'Init_Pos',[0,0,0],'Init_Pos_Vel',[0,0,0],...
          'Course_ANG',0,'RWS',eye(3),'RSW',eye(3),'MaxTargetAng',[0,0,0],'MinTargetAng',[0,0,0],'TargetPos',[0,0,0],'TargetPos_Vel',[0,0,0],'LineTrack_ACC',[0,0,0],'LineTrack_Vel',[0,0,0],'CircleTrc_AngleACC',0.01,'CircleTrc_Radius',10,'CircleTrc_HightACC',0,'PosKP',eye(3),'PosKI',eye(3),'PosKD',eye(3),...
          'AltKP',1,'AltKI',1,'AltKD',1,'TargetAng',[0,0,0],'TargetAng_Vel',[0,0,0],'AngKP',eye(3),'AngKD',eye(3),'RotorKF',1,'HoverRotate',1,'ExpectAngleAcc',[0,0,0]','SlidModeParam',diag([0,0,0]),'SlidModeParamK',diag([0,0,0]),'ReachLawParamE',diag([0,0,0]),'AngleK',diag([0,0,0]),...
          'AngleRateK',diag([0,0,0]),'ChatterBoundar',diag([0,0,0]),'Alfa1',diag([0,0,0]),'Alfa2',diag([0,0,0]),'TraceType',[],'ATTControllerType',[]);

 Mixer=struct('Quad_plus',zeros(4,3),'Quad_X',zeros(4,3),'Hex_plus',zeros(6,3),'Hex_X',zeros(6,3),'Octa_plus',zeros(8,3),'Octa_X',zeros(8,3));
 
  Mixer.Quad_plus=[0,-1,1;
                   1,0,-1;
                   0,1,1;
                   -1,0,-1];
  Mixer.Quad_X=[-cos(pi/4),cos(pi/4),1;
                cos(pi/4),-cos(pi/4),1;
                cos(pi/4),cos(pi/4),-1;
                -cos(pi/4),-cos(pi/4),-1];
  Mixer.Hex_plus=[0,1,-1;
                  0,-1,1;
                  cos(pi/6),-cos(pi/3),-1;
                  -cos(pi/6),cos(pi/3),1;
                  cos(pi/6),cos(pi/3),1;
                  -cos(pi/6),-cos(pi/3),-1];
  Mixer.Hex_X=[-1,0,-1;
                1,0,1;
                cos(pi/3),cos(pi/6),-1;
                -cos(pi/3),-cos(pi/6),1;
                -cos(pi/3),cos(pi/6),1;
                cos(pi/3),-cos(pi/6),-1];
  
  Mixer.Octa_plus=[0,1,-1;
                   0,-1,-1;
                   -cos(pi/4),cos(pi/4),1;
                   -cos(pi/4),-cos(pi/4),1;
                   cos(pi/4),cos(pi/4),1;
                   cos(pi/4),-cos(pi/4),1;
                   1,0,-1;
                   -1,0,-1];
  Mixer.Octa_X=[-cos(3*pi/8),cos(pi/8),-1;
                cos(3*pi/8),-cos(pi/8),-1;
                -cos(pi/8),cos(3*pi/8),1;
                -cos(3*pi/8),-cos(pi/8),1;
                cos(3*pi/8),cos(pi/8),1;
                cos(pi/8),-cos(3*pi/8),1;
                cos(pi/8),cos(3*pi/8),-1;
                -cos(pi/8),-cos(3*pi/8),-1];
 
      
      %%% 给出一组算例
      
      UAV.L=1;                                         %  UAV 力臂,（力作用点到质心的距离）
      UAV.Is=[10,0,0;
              0,10,0;
              0,0,50];                                  %  UAV 转动惯量 只考虑主轴惯量，忽略惯量积 kgm^2
      UAV.Is_inv=inv(UAV.Is);                          % UAV惯量阵的逆
      UAV.Mass=7;                                     %  UAV质量kg
      UAV.Course_ANG=pi/2;                               %  航向角，用于确定机体X轴 rad
      UAV.RWS=[cos(UAV.Course_ANG),-sin(UAV.Course_ANG),0;
               sin(UAV.Course_ANG),cos(UAV.Course_ANG),0;
               0,0,1];                                   % 由NED坐标系到 姿态坐标系的 转换矩阵
      UAV.RSW=UAV.RWS';  
     
      UAV.GravityAcc=9.81;                               %  重力加速度 
      UAV.MaxTargetAng=[0.2,0.2,0.1];                    %  机体允许的最大飞行姿态角， 对目标姿态角做限幅处理 滚转/俯仰/偏航
      UAV.MinTargetAng=-UAV.MaxTargetAng;                %[-0.2,-0.2,-0.1];  % 机体允许的最小飞行姿态角  滚转/俯仰/偏航
      %%%%UAV初始位置参数
      UAV.Init_Pos=[0,0,0];                              %  UAV 初始质心位置 惯性系下
      UAV.Init_Pos_Vel=[0,0,0];                          %  UAV 初始 质心速度 惯性系下
      %%%%
      %%%%质心目标位置
      UAV.TargetPos=[10,20,5];                            % 目标位置；惯性系下（ 调试用）
      UAV.TargetPos_Vel=[0,0,0];                         %  目标速度； 惯性系下（ 调试用）
      %%%%
      %%%%UAV机型参数
      UAV.Type='4x';                                     %UAV 电机排列构型
      %%%%
      %%%%飞行轨迹选择
      UAV.TraceType='Line';                             % 目标飞行轨迹，Line or Circle
      %%%%
      %%%%姿态控制器类型
      UAV.ATTControllerType='PID';%'BackStepping';                           %姿态控制器类型选择 PID/SlidMode/ BackStepping/Fuzzy
      %%%%
      %%%%直线轨迹生成参数
      UAV.LineTrack_ACC=[0,0,0];                             %直线轨迹加速度
      UAV.LineTrack_Vel=[0,1,0];                            % 直线轨迹初始速度
      %%%%
      %%%% 曲线轨迹生成参数
      UAV.CircleTrc_AngleACC=0.0;                         % 圆轨迹角加速度rad/s^2
      UAV.CircleTrc_Radius=10;                              % 轨迹半径m
      UAV.CircleTrc_HightACC=0.0 ;                              %圆轨迹的 高度运动加速度m/s^2
      %%%%
      %%%%水平位置pid控制参数
      UAV.PosKP=20*eye(1);                                %  位置偏差 比例增益
      UAV.PosKD=40*eye(1);                               %  位置偏差 微分增益
      PosKP=UAV.PosKP;
      PosKD=UAV.PosKD;
      %%%%
      %%%%高度pid控制参数
      UAV.AltKP=1;                                      %高度差比例增益
      UAV.AltKI=.01;                                    %高度差 积分增益 
      UAV.AltKD=10;                                      % 高度差 微分增益 
%     AltKP=UAV.AltKP;
%     AltKI=UAV.AltKI;
%     AltKD=UAV.AltKD;
      %%%%end
      UAV.TargetAng=[0.1,0,0];                           % 目标姿态角，（调试用）
      UAV.TargetAng_Vel=[0,0,0];                         % 目标姿态角速度，（调试用）
      %%%%姿态pid控制器参数
%       UAV.AngKP=200*eye(3);                              % 姿态角偏差 比例增益 
%       UAV.AngKD=40*eye(3);  %  姿态偏差  微分增益
%         Kp=10;
%         Kd=5;
     UAV.AngKP=diag([386.0973,386.0973,109.6396]);
     UAV.AngKD=diag([166.3783,166.3783,171.4403]);
     AngKP=UAV.AngKP;
     AngKD=UAV.AngKD;
      %%%%
     UAV.RotorKF=0.05;                                  %  电机参数（满足F=UAV.RotorKF*Omig^2）
   %%%%滑模姿态控制器参数
    UAV.ExpectAngleAcc=[0,0,0]';                       %期望姿态角加速度
    UAV.SlidModeParam= diag([5,5,5]);                       % 姿态滑模面参数lamd
    UAV.SlidModeParamK=diag([10,10,5]);                    % 到达律参数k
    UAV.ReachLawParamE=diag([0.0001,0.0001,0.0001]);              % 到达律参数，ebuxilong
    UAV.AngleK=UAV.SlidModeParamK*UAV.SlidModeParam;        % 
    UAV.AngleRateK=UAV.SlidModeParamK+UAV.SlidModeParam;
    UAV.ChatterBoundar=diag([1/100,1/100,1/100]);           % 滑模控制防振颤边界值
   %%%%
   %%%%姿态反步控制律参数
%    Alfa1=20;
%    Alfa2=20;
   UAV.Alfa1=diag([43.4525,43.4525,38.6833]);
   UAV.Alfa2=diag([42.7588,42.7588,38.6833]);
%    Alfa1=UAV.Alfa1;
%    Alfa2=UAV.Alfa2;
   %%%%
      switch(UAV.Type)
          case '4+'
               UAV.AllocationMoment=UAV.L.*Mixer.Quad_plus';      % UAV  力矩分配矩阵
               UAV.AllocationRotate=Mixer.Quad_plus;      %电机转速分配
               UAV.RotorNum=4;                            % 电机个数；
          case '4x'
               UAV.AllocationMoment=UAV.L.*Mixer.Quad_X';            % 4x 与4X 一样
               UAV.AllocationRotate=Mixer.Quad_X;
               UAV.RotorNum=4;
          case '4X'
               UAV.AllocationMoment=UAV.L.*Mixer.Quad_X';
               UAV.AllocationRotate=Mixer.Quad_X;
               UAV.RotorNum=4;
          case '6+'
               UAV.AllocationMoment=UAV.L.*Mixer.Hex_plus';
               UAV.AllocationRotate=Mixer.Hex_plus;
               UAV.RotorNum=6;
          case '6x' 
               UAV.AllocationMoment=UAV.L.*Mixer.Hex_X';
               UAV.AllocationRotate=Mixer.Hex_X;
               UAV.RotorNum=6;
          case '6X'
               UAV.AllocationMoment=UAV.L.*Mixer.Hex_X';     % 6x=6X
               UAV.AllocationRotate=Mixer.Hex_X;
               UAV.RotorNum=6;
          case '8+'
               UAV.AllocationMoment=UAV.L.*Mixer.Octa_plus';
               UAV.AllocationRotate=Mixer.Octa_plus;
               UAV.RotorNum=8;
          case '8x'
               UAV.AllocationMoment=UAV.L.*Mixer.Octa_X';
               UAV.AllocationRotate=Mixer.Octa_X;
               UAV.RotorNum=8;
          case '8X'
               UAV.AllocationMoment=UAV.L.*Mixer.Octa_X';  %8x=8X
               UAV.AllocationRotate=Mixer.Octa_X;
               UAV.RotorNum=8;
          otherwise;
              errordlg('系统暂没有要选择的构型');
      end
      switch(UAV.TraceType)
          case 'Line'
             UAV.TraceType=1;
          case 'Circle'
             UAV.TraceType=2;
          otherwise
             errordlg('系统暂没有要选择的轨迹生成器'); 
      end
      switch(UAV.ATTControllerType)
          case 'PID'
             UAV.ATTControllerType=1;
          case 'SlidMode'
             UAV.ATTControllerType=2;
          case 'BackStepping'
             UAV.ATTControllerType=3;
          case 'Fuzzy'
             UAV.ATTControllerType=4;
          otherwise
              errordlg('系统暂没有要选择的姿态控制器'); 
      end
              
      UAV.HoverRotate=sqrt(UAV.Mass*UAV.GravityAcc/(UAV.RotorNum*UAV.RotorKF));    %  悬停时的电机转速  