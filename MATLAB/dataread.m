function dataout = dataread (filein, fileout, line)

fidin = fopen(filein,'r');

fidout = fopen(fileout,'w');

nline=0;


while ~feof(fidin) % �P�_�O�_����󥽧�

    tline=fgetl(fidin); % �q���Ū��

    nline=nline+1;

    if nline == line

        fprintf(fidout,'%s\n',tline);

        dataout = tline;

    end

end

fclose(fidin);

fclose(fidout);