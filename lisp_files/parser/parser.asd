;;;; parser.asd

(asdf:defsystem #:parser
  :description "Describe parser here"
  :author "Your Name <your.name@example.com>"
  :license "Specify license here"
  :depends-on (:cl-ppcre :alexandria)
               
  :serial t
  :components ((:file "parser")))

