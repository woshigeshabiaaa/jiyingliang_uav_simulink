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
 
      
      %%% ����һ������
      
      UAV.L=1;                                         %  UAV ����,�������õ㵽���ĵľ��룩
      UAV.Is=[10,0,0;
              0,10,0;
              0,0,50];                                  %  UAV ת������ ֻ����������������Թ����� kgm^2
      UAV.Is_inv=inv(UAV.Is);                          % UAV���������
      UAV.Mass=7;                                     %  UAV����kg
      UAV.Course_ANG=pi/2;                               %  ����ǣ�����ȷ������X�� rad
      UAV.RWS=[cos(UAV.Course_ANG),-sin(UAV.Course_ANG),0;
               sin(UAV.Course_ANG),cos(UAV.Course_ANG),0;
               0,0,1];                                   % ��NED����ϵ�� ��̬����ϵ�� ת������
      UAV.RSW=UAV.RWS';  
     
      UAV.GravityAcc=9.81;                               %  �������ٶ� 
      UAV.MaxTargetAng=[0.2,0.2,0.1];                    %  �����������������̬�ǣ� ��Ŀ����̬�����޷����� ��ת/����/ƫ��
      UAV.MinTargetAng=-UAV.MaxTargetAng;                %[-0.2,-0.2,-0.1];  % �����������С������̬��  ��ת/����/ƫ��
      %%%%UAV��ʼλ�ò���
      UAV.Init_Pos=[0,0,0];                              %  UAV ��ʼ����λ�� ����ϵ��
      UAV.Init_Pos_Vel=[0,0,0];                          %  UAV ��ʼ �����ٶ� ����ϵ��
      %%%%
      %%%%����Ŀ��λ��
      UAV.TargetPos=[10,20,5];                            % Ŀ��λ�ã�����ϵ�£� �����ã�
      UAV.TargetPos_Vel=[0,0,0];                         %  Ŀ���ٶȣ� ����ϵ�£� �����ã�
      %%%%
      %%%%UAV���Ͳ���
      UAV.Type='4x';                                     %UAV ������й���
      %%%%
      %%%%���й켣ѡ��
      UAV.TraceType='Line';                             % Ŀ����й켣��Line or Circle
      %%%%
      %%%%��̬����������
      UAV.ATTControllerType='PID';%'BackStepping';                           %��̬����������ѡ�� PID/SlidMode/ BackStepping/Fuzzy
      %%%%
      %%%%ֱ�߹켣���ɲ���
      UAV.LineTrack_ACC=[0,0,0];                             %ֱ�߹켣���ٶ�
      UAV.LineTrack_Vel=[0,1,0];                            % ֱ�߹켣��ʼ�ٶ�
      %%%%
      %%%% ���߹켣���ɲ���
      UAV.CircleTrc_AngleACC=0.0;                         % Բ�켣�Ǽ��ٶ�rad/s^2
      UAV.CircleTrc_Radius=10;                              % �켣�뾶m
      UAV.CircleTrc_HightACC=0.0 ;                              %Բ�켣�� �߶��˶����ٶ�m/s^2
      %%%%
      %%%%ˮƽλ��pid���Ʋ���
      UAV.PosKP=20*eye(1);                                %  λ��ƫ�� ��������
      UAV.PosKD=40*eye(1);                               %  λ��ƫ�� ΢������
      PosKP=UAV.PosKP;
      PosKD=UAV.PosKD;
      %%%%
      %%%%�߶�pid���Ʋ���
      UAV.AltKP=1;                                      %�߶Ȳ��������
      UAV.AltKI=.01;                                    %�߶Ȳ� �������� 
      UAV.AltKD=10;                                      % �߶Ȳ� ΢������ 
%     AltKP=UAV.AltKP;
%     AltKI=UAV.AltKI;
%     AltKD=UAV.AltKD;
      %%%%end
      UAV.TargetAng=[0.1,0,0];                           % Ŀ����̬�ǣ��������ã�
      UAV.TargetAng_Vel=[0,0,0];                         % Ŀ����̬���ٶȣ��������ã�
      %%%%��̬pid����������
%       UAV.AngKP=200*eye(3);                              % ��̬��ƫ�� �������� 
%       UAV.AngKD=40*eye(3);  %  ��̬ƫ��  ΢������
%         Kp=10;
%         Kd=5;
     UAV.AngKP=diag([386.0973,386.0973,109.6396]);
     UAV.AngKD=diag([166.3783,166.3783,171.4403]);
     AngKP=UAV.AngKP;
     AngKD=UAV.AngKD;
      %%%%
     UAV.RotorKF=0.05;                                  %  �������������F=UAV.RotorKF*Omig^2��
   %%%%��ģ��̬����������
    UAV.ExpectAngleAcc=[0,0,0]';                       %������̬�Ǽ��ٶ�
    UAV.SlidModeParam= diag([5,5,5]);                       % ��̬��ģ�����lamd
    UAV.SlidModeParamK=diag([10,10,5]);                    % �����ɲ���k
    UAV.ReachLawParamE=diag([0.0001,0.0001,0.0001]);              % �����ɲ�����ebuxilong
    UAV.AngleK=UAV.SlidModeParamK*UAV.SlidModeParam;        % 
    UAV.AngleRateK=UAV.SlidModeParamK+UAV.SlidModeParam;
    UAV.ChatterBoundar=diag([1/100,1/100,1/100]);           % ��ģ���Ʒ�����߽�ֵ
   %%%%
   %%%%��̬���������ɲ���
%    Alfa1=20;
%    Alfa2=20;
   UAV.Alfa1=diag([43.4525,43.4525,38.6833]);
   UAV.Alfa2=diag([42.7588,42.7588,38.6833]);
%    Alfa1=UAV.Alfa1;
%    Alfa2=UAV.Alfa2;
   %%%%
      switch(UAV.Type)
          case '4+'
               UAV.AllocationMoment=UAV.L.*Mixer.Quad_plus';      % UAV  ���ط������
               UAV.AllocationRotate=Mixer.Quad_plus;      %���ת�ٷ���
               UAV.RotorNum=4;                            % ���������
          case '4x'
               UAV.AllocationMoment=UAV.L.*Mixer.Quad_X';            % 4x ��4X һ��
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
              errordlg('ϵͳ��û��Ҫѡ��Ĺ���');
      end
      switch(UAV.TraceType)
          case 'Line'
             UAV.TraceType=1;
          case 'Circle'
             UAV.TraceType=2;
          otherwise
             errordlg('ϵͳ��û��Ҫѡ��Ĺ켣������'); 
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
              errordlg('ϵͳ��û��Ҫѡ�����̬������'); 
      end
              
      UAV.HoverRotate=sqrt(UAV.Mass*UAV.GravityAcc/(UAV.RotorNum*UAV.RotorKF));    %  ��ͣʱ�ĵ��ת��  