clear all;

fid = fopen('LongPressEasy.txt');
logdata = textscan(fid, '%f64 %d %s %d %d %f64');
fclose(fid);

finger = logdata{2};
state = logdata{3};
X = logdata{4};
Y = logdata{5};
% r: red     * : target and target range
% r: red     o : (finger) end
% r: red     X : (task) end
% g: green   o : (finger) begin
% g: green   X : (task)hit
% k: black    - : 0 finger move
% 'color', [0 0.38 0.2] : 藍綠色    - : 1 finger move
% m: megenta - : 2 finger move
% b: blue   - : 3 finger move
% 'color', [1 0.65 0] : orange - : 4 finger move

zeroX(1:100) = 0;
zeroY(1:100) = 0;
oneX(1:100) = 0;
oneY(1:100) = 0;
twoX(1:100) = 0;
twoY(1:100) = 0;
threeX(1:100) = 0;
threeY(1:100) = 0;
fourX(1:100) = 0;
fourY(1:100) = 0;
% 檢查是不是整個task的end，應該要遇到-3的end 才fig++，還沒寫。
%flag_NewBegin = 1; % 濾掉task完成後還在持續的move//think about it

% hit 用來蓋色
hitX(1:5) = 0;
hitY(1:5) = 0;
hit_count = 1;

% Offset
OffsetX = 0;
OffsetY = 0;

TargetX = 0;
TargetY = 0;
% Target Size
TRX(1:5) = 0;
TRY(1:5) = 0;

T0_count = 1;
T1_count = 1;
T2_count = 1;
T3_count = 1;
T4_count = 1;

for i = 1:874
    switch finger(i)
        case 0
            if strcmp(state(i), 'begin')
                plot(X(i)-TargetX, -Y(i)-TargetY, 'o');
            end
        case 1
            if strcmp(state(i), 'begin')
                plot(X(i)-TargetX, -Y(i)-TargetY, 'o');
            end
        case 2
            if strcmp(state(i), 'begin')
                plot(X(i)-TargetX, -Y(i)-TargetY, 'o');
            end
        case 3
            if strcmp(state(i), 'begin')
                plot(X(i)-TargetX, -Y(i)-TargetY, 'o');
            end
        case 4
            if strcmp(state(i), 'begin')
                plot(X(i)-TargetX, -Y(i)-TargetY, 'o');
            end
        case -3
            if strcmp(state(i), 'hit')
                hitX(hit_count) = X(i)-TargetX;
                hitY(hit_count) = -Y(i)-TargetY;
                hit_count = hit_count+1;
            elseif strcmp(state(i), 'end')
                %放後面是為了蓋色
                %plot(X(i)-TargetX, -Y(i)-TargetY, 'rX');
                plot(hitX(1:hit_count-1), hitY(1:hit_count-1), 'X');
                hit_count = 1;
            elseif strcmp(state(i), 'start')
                hit_count = 1;
                TargetX = X(i)+22;
                TargetY = -Y(i)-22;
                TRX(1) = -22;
                TRY(1) = +22;
                TRX(2) = TRX(1) + 44;
                TRY(2) = TRY(1);
                TRX(3) = TRX(2);
                TRY(3) = TRY(2) - 44;
                TRX(4) = TRX(1);
                TRY(4) = TRY(3);
                TRX(5) = TRX(1);
                TRY(5) = TRY(1);
                plot(TRX(1:5), TRY(1:5), 'r--');
                hold on;
                plot(300, -300, 'r*');
            else
                disp('Error: There is worng status in -3 case');
            end
        otherwise
            disp('Error: The finger index is over than 4');
            disp(i);
    end        
%     if strcmp(state(i), 'move')
%             switch(finger(i-1))
%                 case 0
%                     plot(zeroX(1:T0_count), zeroY(1:T0_count),'-ko');
%                     T0_count = 1;
%                 case 1
%                     plot(oneX(1:T1_count), oneY(1:T1_count),'-co');
%                     T1_count = 1;
%                 case 2
%                     plot(twoX(1:T2_count), twoY(1:T2_count),'-mo');
%                     T2_count = 1;
%                 case 3
%                     plot(threeX(1:T3_count), threeY(1:T3_count),'-bo');
%                     T3_count = 1;
%                 case 4
%                     plot(fourX(1:T4_count),fourY(1:T4_count),'color', [1 0.65 0], '-o');
%                     T4_count = 1;
%                 otherwise
%                     disp('Error: The finger index is over than 4');
%                     disp(i);
%             end
%             T0_count = 1;
%             T1_count = 1;
%             T2_count = 1;
%             T3_count = 1;
%             T4_count = 1;
%     end
end
grid on;
set(gcf,'Units','centimeters','position',[0.1 0.1 60 30]);
print(gcf, '-dpng', '-r500', 'All.png');
        
        