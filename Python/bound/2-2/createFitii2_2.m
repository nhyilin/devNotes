function [fitresult] = createFitii2_2(xii, yii)
%CREATEFIT(XII,YII)
%  Create a fit.
%
%  Data for 'untitled fit 1' fit:
%      X Input : xii
%      Y Output: yii
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 02-Feb-2021 21:34:20 自动生成


%% Fit: 'untitled fit 1'.
[xData, yData] = prepareCurveData( xii, yii );

% Set up fittype and options.
ft = fittype( 'poly1' );

% Fit model to data.
[fitresult,~] = fit( xData, yData, ft );

% Plot fit with data.
% figure( 'Name', 'untitled fit 1' );
% h = plot( fitresult, xData, yData );
% legend( h, 'yii vs. xii', 'untitled fit 1', 'Location', 'NorthEast' );
% % Label axes
% xlabel xii
% ylabel yii
% grid on


