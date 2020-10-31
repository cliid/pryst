package org.jitcijk.pryst.runtime;

import com.oracle.truffle.api.nodes.Node;

public class PrystRuntimeException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    public PrystRuntimeException(Node node, String arg0, Throwable arg1) {
        super(nodeDescription(node) + arg0, arg1);
    }

    public PrystRuntimeException(Node node, String arg0) {
        super(nodeDescription(node) + arg0);
    }

    public PrystRuntimeException(Node node, Throwable arg0) {
        super(nodeDescription(node) + arg0.getMessage(), arg0);
    }

    private static String nodeDescription(Node node) {
        return node.getSourceSection().getSource().getName()+":"+node.getSourceSection().getStartLine()+": " + node.getSourceSection().getSource().getCharacters().toString()+": ";
    }
}
