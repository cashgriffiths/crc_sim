To run the C simulation, use the following syntax:
./crc_sim.exe <g> <k> <iter>
where <g> is the generator polynomial represented as a hexadecimal string e.g. 0x11021,
<k> is the data length, and <iter> is the number of iterations to perform (1000000=1e6 recommended)

To run the Matlab simulation, use the following syntax:
crc_sim <g> <k> <iter>
where <g> is the generator polynomial represented as a list of binary coeffecients e.g. [1 0 0 1 1 0 1 0]
<k> is the data length, and <iter> is the number of iterations to perform (1000000=1e6 recommended)
