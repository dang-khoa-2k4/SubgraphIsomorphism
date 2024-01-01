clc;
inc_mtx_file = 'C:\Users\ADMIN\OneDrive - hcmut.edu.vn\University\Sophomore\Discrete Mathematics\Assignment\Graph\output\ktruss_input.txt';
test_file = '../../../data/test.tsv';

E_expected =  [1  1  0  0  0; ...
               0  1  1  0  0; ...
               1  0  0  1  0; ...
               0  0  1  1  0; ...
               1  0  1  0  0; ...
               0  0  0  0  0];


E = ktruss(inc_mtx_file, 6);


%if nnz( full(E) - E_expected )
 %   fprintf(2, 'Unable to verify results\n');
%else

%disp(E);
size = nnz(E);
fprintf('%d\n', size);
V = sparse(E' * E);
%disp(V);
%end
%fileID = fopen('../../../data/file.txt', 'w');



fprintf('done\n');
