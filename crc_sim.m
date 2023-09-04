function u = crc_sim(g, k, iter)
tic
n = k + length(g) - 1;

% generate arbitrary message
m = randi([0, 1], 1, k);

% produce message
c = mod(conv(m, g), 2);

s = 0;
for ii = 1:iter
    % produce error
    e = randi([0, 1], 1, n);
    
    % attempt message recovery
    [~, rem] = deconv(c + e, g);
    
    % check if remainder polynomial is zero
    rem = sum(mod(rem, 2));
    if rem ~= 0
         s = s + 1;
    end
end

% increase precision
vpa(s / iter)
toc