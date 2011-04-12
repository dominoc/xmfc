function plot_data(in_data,in_titles)

figure;

    for(p=1:4)
        subplot(2,2,p);
        plot(in_data{p});
        hold on;
        % Hack to let Octave cast it to String...
        title(['' in_titles(p)]);
        legend('x','y','z');
        hold off;
    end
    
end