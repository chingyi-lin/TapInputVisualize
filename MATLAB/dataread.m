function dataout = dataread (filein, fileout, line)

fidin = fopen(filein,'r');

fidout = fopen(fileout,'w');

nline=0;


while ~feof(fidin) % 判斷是否為文件末尾

    tline=fgetl(fidin); % 從文件讀行

    nline=nline+1;

    if nline == line

        fprintf(fidout,'%s\n',tline);

        dataout = tline;

    end

end

fclose(fidin);

fclose(fidout);