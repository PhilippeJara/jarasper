(require 'asdf)

(case (push "./lisp_files/parser/"  asdf:*central-registry*)
  (t (format t "parser pushed to central registry ~%")))
(case (asdf:make-build :parser
		       :type :fasl
		       :monolithic t
		       :move-here "./lisp_files/parser")
  (t (format t "parser built ~%")))
(case (push "./lisp_files/runtime/"  asdf:*central-registry*)
  (t (format t "runtime pushed to central registry  ~%")))
(case (asdf:make-build :runtime
		       :type :static-library
		       :monolithic t
		       :move-here "./lisp_files/runtime")
  (t (format t "runtime built ~%")))


