%module ortcxx

%{
    #include "core.h"
    #include "serviceManager.h"
%}

%include "core.h"
%include "serviceManager.h"

%ignore cinrt::model::Model::runAsync;
%include "async_helper.h"