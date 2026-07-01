from lru_bridge import LruCacheBridge

if __name__ == "__main__":
    # Max cache capacity size boundary limit
    rag_cache = LruCacheBridge(capacity=2)

    print("=== SECURLRU-RAG OPTIMIZED INGESTION CONTEXT CACHE ===")
    
    # Simulate caching active query maps to avoid raw generation logic drops
    rag_cache.push_context("CVE-2026-001", "Playbook: Patch system memory allocation bounds inside kernel stack pointers.")
    rag_cache.push_context("CVE-2026-002", "Playbook: Enforce explicit validation transformations across cross-origin frames.")

    # Access context 1 (Moves node item to head location pointers position mapping)
    print(f"[*] Querying context for CVE-2026-001 (Cache Read):\n -> {rag_cache.fetch_context('CVE-2026-001')}")

    # Evict oldest entry (CVE-2026-002) by pushing a third key mapping profile
    print("\n[*] Injecting new security playbooks data. Forcing capacity boundaries eviction rules...")
    rag_cache.push_context("CVE-2026-003", "Playbook: Rotate master authentication credentials across infrastructure layers.")

    # Validate eviction state anomalies
    print(f"\n[*] Querying evicted node item (CVE-2026-002):\n -> {rag_cache.fetch_context('CVE-2026-002')}")
