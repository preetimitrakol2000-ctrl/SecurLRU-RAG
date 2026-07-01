# SecurLRU-RAG // High-Velocity Context Cache for Large Language Models

An acceleration middleware layout pairing Hash Node indexing with Doubly Linked Lists in C to handle lightning-fast $O(1)$ hit extractions of repeatedly requested security playbooks.

## Infrastructure Framework
- **Eviction Core ($O(1)$):** Automatically dumps long-tail background knowledge allocations to conserve local memory during massive log stream queries.
- **Binding Layer:** Uses direct memory translation to keep Python pipeline memory footprints low.

## Running Tests
```bash
python cached_rag_pipeline.py
