function analyze(in_listFilename)

[data, locs] = handle_mtbFiles(in_listFilename);

l_N = length(data);

    for(i = 1:l_N)
        statistics = detect_steps(data{i},locs);
    end

end