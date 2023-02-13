function [fitresult] = createFit2_2(X, Y, Z)
%CREATEFIT(X,Y,Z)
%  Create a fit.
%
%  Data for 'untitled fit 1' fit:
%      X Input : X
%      Y Input : Y
%      Z Output: Z
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  ������� FIT, CFIT, SFIT.

%  �� MATLAB �� 02-Feb-2021 20:22:40 �Զ�����


%% Fit: 'untitled fit 1'.
[xData, yData, zData] = prepareSurfaceData( X, Y, Z );

% Set up fittype and options.
ft = fittype( 'poly11' );

% Fit model to data.
[fitresult,~] = fit( [xData, yData], zData, ft );

% Plot fit with data.
% figure( 'Name', 'untitled fit 1' );
% h = plot( fitresult, [xData, yData], zData );
% legend( h, 'untitled fit 1', 'Z vs. X, Y', 'Location', 'NorthEast' );
% % Label axes
% xlabel X
% ylabel Y
% zlabel Z
% grid on
% view( 81.2, 3.1 );


