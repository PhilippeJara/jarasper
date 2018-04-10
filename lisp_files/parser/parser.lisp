;;;; parser.lisp
(defpackage :parser
  (:use :cl :cl-ppcre :alexandria)
  (:export :load-notice :looker))
(in-package :parser)
(print "FASL loaded")
(defun looker (look)
  (describe look)
  (princ look))
(defun load-notice ()
    (princ (ppcre:all-matches-as-strings ".+" "PPCRE"))
    )
(defvar path "~//projects//jarasper//llvmir.ll")

(defun parse-llvm-IR (path)
  (with-open-file (stream path)
    (cl-ppcre:all-matches-as-strings "define.+?{[.+?]}" stream)))

(defun read-all-lines-to-string (path)
  (with-open-file (stream path)
    (let (string final-string)
      (loop for temp-string = (read-line stream :eof-error-p nil)
	 :while temp-string
	 :do (append final-string temp-string )))))



;; (with-open-file (s path)
;;     (do ((l (read-line s) (read-line s nil 'eof)))))
        
