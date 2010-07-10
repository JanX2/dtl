/**
   dtl-1.07 -- Diff Template Library
   
   In short, Diff Template Library is distributed under so called "BSD license",
   
   Copyright (c) 2008-2010 Tatsuhiko Kubo <cubicdaiya@gmail.com>
   All rights reserved.
   
   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:
   
   * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
   
   * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
   
   * Neither the name of the authors nor the names of its contributors
   may be used to endorse or promote products derived from this software 
   without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* If you use this library, you must include dtl.hpp only. */

#ifndef DTL_FUNCTORS_H
#define DTL_FUNCTORS_H

namespace dtl {
    
    /**
     * printer class template
     */
    template <typename sesElem>
    class Printer
    {
    public :
        Printer ()             : out_(cout) {}
        Printer (ostream& out) : out_(out)  {}
        virtual ~Printer () {}
        virtual void operator() (const sesElem& se) const = 0;
    protected :
        ostream& out_;
    };
    
    /**
     * common element printer class template
     */
    template <typename sesElem>
    class CommonPrinter : public Printer < sesElem >
    {
    public :
        CommonPrinter  ()             : Printer < sesElem > ()    {}
        CommonPrinter  (ostream& out) : Printer < sesElem > (out) {}
        ~CommonPrinter () {}
        void operator() (const sesElem& se) const {
            this->out_ << SES_MARK_COMMON << se.first << endl;    
        }
    };
    
    /**
     * ses element printer class template
     */
    template <typename sesElem>
    class ChangePrinter : public Printer < sesElem >
    {
    public :
        ChangePrinter  ()             : Printer < sesElem > ()    {}
        ChangePrinter  (ostream& out) : Printer < sesElem > (out) {}
        ~ChangePrinter () {}
        void operator() (const sesElem& se) const {
            switch (se.second.type) {
            case SES_ADD:
                this->out_ << SES_MARK_ADD    << se.first << endl;
                break;
            case SES_DELETE:
                this->out_ << SES_MARK_DELETE << se.first << endl;
                break;
            case SES_COMMON:
                this->out_ << SES_MARK_COMMON << se.first << endl;
                break;
            }
        }
    };
    
    /**
     * unfiend format element printer class template
     */
    template <typename sesElem>
    class UniHunkPrinter
    {
    public :
        UniHunkPrinter  ()             : out_(cout) {}
        UniHunkPrinter  (ostream& out) : out_(out)  {}
        ~UniHunkPrinter () {}
        void operator() (const uniHunk< sesElem >& hunk) const {
            out_ << "@@"
                 << " -"  << hunk.a << "," << hunk.b
                 << " +"  << hunk.c << "," << hunk.d
                 << " @@" << endl;
            
            for_each(hunk.common[0].begin(), hunk.common[0].end(), CommonPrinter< sesElem >());
            for_each(hunk.change.begin(),    hunk.change.end(),    ChangePrinter< sesElem >());
            for_each(hunk.common[1].begin(), hunk.common[1].end(), CommonPrinter< sesElem >());
        }
    private :
        ostream& out_;
    };
    
    /**
     * compare class template
     */
    template <typename elem>
    class Compare
    {
    public :
        Compare () {}
        virtual ~Compare () {}
        virtual bool impl (const elem& e1, const elem& e2) const {
            return e1 == e2;
        }
    };
}

#endif // DTL_FUNCTORS_H
