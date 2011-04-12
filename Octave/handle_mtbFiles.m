function [ret_data,ret_loc] = handle_mtbFiles(in_fileListFileName)

l_fh = fopen(in_fileListFileName,'r');

ret_data = cell(0);

l_cnt  = 1;
l_line = fgetl(l_fh);


while(l_line ~= -1)
    [ret_data{l_cnt},ret_loc] = process_data(l_line);
    l_cnt = l_cnt+1;
    l_line = fgetl(l_fh);
end

fclose(l_fh);

end