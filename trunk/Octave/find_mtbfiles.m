function file_list = find_mtbFiles(in_dirs)

file_list = cell(0);
l_cnt = 1;

for(l_cd = 1:length(in_dirs)) 
    l_curDir = in_dirs(l_cd);
    l_dirCont = dir(l_curDir);
    l_n = length(l_dirCont);
    
    for( e = 1:l_n) % go over all entries
        l_e = l_dirCont(e);
        if(l_e.isDir)
            continue;
        end
        
        if(l_e.name == '.' || l_e.name == '..')
            continue;
        end
        
        % start, end, extents of each matched, cell array of the
        % text of each match, cell array of the text of each token
        % matched, text and name
        [s,e,te,m,t,nm] = regexp(e.name,'.*\.mtb','ignorecase');
        
        if(length(s) == 0) 
            continue;
        end
        
        file_list{cnt} = m;
        cnt = cnt+1;
        
    end
    
end